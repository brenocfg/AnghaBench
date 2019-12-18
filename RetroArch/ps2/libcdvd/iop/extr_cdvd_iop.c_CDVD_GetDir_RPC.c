#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct t_SifDmaTransfer {int size; scalar_t__ attr; struct TocEntry* dest; struct TocEntry* src; } ;
struct dirTocEntry {int length; int fileProperties; } ;
struct TocEntry {int /*<<< orphan*/  filename; } ;
typedef  enum CDVD_getMode { ____Placeholder_CDVD_getMode } CDVD_getMode ;
struct TYPE_2__ {int sector_num; char const* pathname; char* cache; scalar_t__ path_depth; int cache_size; scalar_t__ cache_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NEXT ; 
 int /*<<< orphan*/  CACHE_START ; 
 scalar_t__ CDVD_Cache_Dir (char const*,int /*<<< orphan*/ ) ; 
 int CDVD_GET_DIRS_ONLY ; 
 int CDVD_GET_FILES_AND_DIRS ; 
 int CDVD_GET_FILES_ONLY ; 
 TYPE_1__ CachedDirInfo ; 
 int /*<<< orphan*/  CpuResumeIntr (int) ; 
 int /*<<< orphan*/  CpuSuspendIntr (int*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ TocEntryCompare (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  TocEntryCopy (struct TocEntry*,struct dirTocEntry*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ sceSifDmaStat (int) ; 
 int sceSifSetDma (struct t_SifDmaTransfer*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char const*) ; 

int CDVD_GetDir_RPC(const char *pathname, const char *extensions, enum CDVD_getMode getMode, struct TocEntry tocEntry[], unsigned int req_entries)
{
    int matched_entries;
    int dir_entry;

    struct TocEntry localTocEntry;

    struct dirTocEntry *tocEntryPointer;

    int intStatus;  // interrupt status - for dis/en-abling interrupts

    struct t_SifDmaTransfer dmaStruct;
    int dmaID;

    dmaID = 0;

#ifdef DEBUG
    printf("RPC GetDir Request\n");
#endif

    matched_entries = 0;

    // pre-cache the dir (and get the new pathname - in-case selected "..")
    if (CDVD_Cache_Dir(pathname, CACHE_START) != TRUE) {
#ifdef DEBUG
        printf("CDVD_GetDir_RPC - Call of CDVD_Cache_Dir failed\n");
#endif

        return -1;
    }

#ifdef DEBUG
    printf("requested directory is %d sectors\n", CachedDirInfo.sector_num);
#endif

    if ((getMode == CDVD_GET_DIRS_ONLY) || (getMode == CDVD_GET_FILES_AND_DIRS)) {
        // Cache the start of the requested directory
        if (CDVD_Cache_Dir(CachedDirInfo.pathname, CACHE_START) != TRUE) {
#ifdef DEBUG
            printf("CDVD_GetDir_RPC - Call of CDVD_Cache_Dir failed\n");
#endif

            return -1;
        }

        tocEntryPointer = (struct dirTocEntry *)CachedDirInfo.cache;

        // skip the first self-referencing entry
        tocEntryPointer = (struct dirTocEntry *)((u8 *)tocEntryPointer + tocEntryPointer->length);

        // skip the parent entry if this is the root
        if (CachedDirInfo.path_depth == 0)
            tocEntryPointer = (struct dirTocEntry *)((u8 *)tocEntryPointer + tocEntryPointer->length);

        dir_entry = 0;

        while (1) {
#ifdef DEBUG
            printf("CDVD_GetDir_RPC - inside while-loop\n");
#endif

            // parse the current cache block
            for (; tocEntryPointer < (struct dirTocEntry *)(CachedDirInfo.cache + (CachedDirInfo.cache_size * 2048)); tocEntryPointer = (struct dirTocEntry *)((u8 *)tocEntryPointer + tocEntryPointer->length)) {
                if (tocEntryPointer->length == 0) {
                    // if we have a toc entry length of zero,
                    // then we've either reached the end of the sector, or the end of the dir
                    // so point to next sector (if there is one - will be checked by next condition)

                    tocEntryPointer = (struct dirTocEntry *)(CachedDirInfo.cache + (((((char *)tocEntryPointer - CachedDirInfo.cache) / 2048) + 1) * 2048));
                }

                if (tocEntryPointer >= (struct dirTocEntry *)(CachedDirInfo.cache + (CachedDirInfo.cache_size * 2048))) {
                    // we've reached the end of the current cache block (which may be end of entire dir
                    // so just break the loop
                    break;
                }

                // Check if the current entry is a dir or a file
                if (tocEntryPointer->fileProperties & 0x02) {
#ifdef DEBUG
                    printf("We found a dir, and we want all dirs\n");
#endif

                    // wait for any previous DMA to complete
                    // before over-writing localTocEntry
                    while (sceSifDmaStat(dmaID) >= 0)
                        ;

                    TocEntryCopy(&localTocEntry, tocEntryPointer);

                    if (dir_entry == 0) {
                        if (CachedDirInfo.path_depth != 0) {
#ifdef DEBUG
                            printf("It's the first directory entry, so name it '..'\n");
#endif

                            strcpy(localTocEntry.filename, "..");
                        }
                    }

                    // DMA localTocEntry to the address specified by tocEntry[matched_entries]

                    // setup the dma struct
                    dmaStruct.src = &localTocEntry;
                    dmaStruct.dest = &tocEntry[matched_entries];
                    dmaStruct.size = sizeof(struct TocEntry);
                    dmaStruct.attr = 0;

                    // Do the DMA transfer
                    CpuSuspendIntr(&intStatus);

                    dmaID = sceSifSetDma(&dmaStruct, 1);

                    CpuResumeIntr(intStatus);

                    matched_entries++;
                } else  // it must be a file
                {
#ifdef DEBUG
                    printf("We found a file, but we dont want files (at least not yet)\n");
#endif
                }

                dir_entry++;

                if (matched_entries >= req_entries)  // if we've filled the requested buffer
                    return (matched_entries);        // then just return

            }  // end of the current cache block

            // if there is more dir to load, then load next chunk, else finish
            if ((CachedDirInfo.cache_offset + CachedDirInfo.cache_size) < CachedDirInfo.sector_num) {
                if (CDVD_Cache_Dir(CachedDirInfo.pathname, CACHE_NEXT) != TRUE) {
                    // failed to cache next block (should return TRUE even if
                    // there is no more directory, as long as a CD read didnt fail
                    return -1;
                }
            } else
                break;

            tocEntryPointer = (struct dirTocEntry *)CachedDirInfo.cache;
        }
    }

    // Next do files
    if ((getMode == CDVD_GET_FILES_ONLY) || (getMode == CDVD_GET_FILES_AND_DIRS)) {
        // Cache the start of the requested directory
        if (CDVD_Cache_Dir(CachedDirInfo.pathname, CACHE_START) != TRUE) {
#ifdef DEBUG
            printf("CDVD_GetDir_RPC - Call of CDVD_Cache_Dir failed\n");
#endif

            return -1;
        }

        tocEntryPointer = (struct dirTocEntry *)CachedDirInfo.cache;

        // skip the first self-referencing entry
        tocEntryPointer = (struct dirTocEntry *)((u8 *)tocEntryPointer + tocEntryPointer->length);

        // skip the parent entry if this is the root
        if (CachedDirInfo.path_depth == 0)
            tocEntryPointer = (struct dirTocEntry *)((u8 *)tocEntryPointer + tocEntryPointer->length);

        dir_entry = 0;

        while (1) {
#ifdef DEBUG
            printf("CDVD_GetDir_RPC - inside while-loop\n");
#endif

            // parse the current cache block
            for (; tocEntryPointer < (struct dirTocEntry *)(CachedDirInfo.cache + (CachedDirInfo.cache_size * 2048)); tocEntryPointer = (struct dirTocEntry *)((u8 *)tocEntryPointer + tocEntryPointer->length)) {
                if (tocEntryPointer->length == 0) {
                    // if we have a toc entry length of zero,
                    // then we've either reached the end of the sector, or the end of the dir
                    // so point to next sector (if there is one - will be checked by next condition)

                    tocEntryPointer = (struct dirTocEntry *)(CachedDirInfo.cache + (((((char *)tocEntryPointer - CachedDirInfo.cache) / 2048) + 1) * 2048));
                }

                if (tocEntryPointer >= (struct dirTocEntry *)(CachedDirInfo.cache + (CachedDirInfo.cache_size * 2048))) {
                    // we've reached the end of the current cache block (which may be end of entire dir
                    // so just break the loop
                    break;
                }

                // Check if the current entry is a dir or a file
                if (tocEntryPointer->fileProperties & 0x02) {
#ifdef DEBUG
                    printf("We don't want files now\n");
#endif
                } else  // it must be a file
                {
                    // wait for any previous DMA to complete
                    // before over-writing localTocEntry
                    while (sceSifDmaStat(dmaID) >= 0)
                        ;

                    TocEntryCopy(&localTocEntry, tocEntryPointer);

                    if (strlen(extensions) > 0) {
                        // check if the file matches the extension list
                        if (TocEntryCompare(localTocEntry.filename, extensions) == TRUE) {
#ifdef DEBUG
                            printf("We found a file that matches the requested extension list\n");
#endif

                            // DMA localTocEntry to the address specified by tocEntry[matched_entries]

                            // setup the dma struct
                            dmaStruct.src = &localTocEntry;
                            dmaStruct.dest = &tocEntry[matched_entries];
                            dmaStruct.size = sizeof(struct TocEntry);
                            dmaStruct.attr = 0;

                            // Do the DMA transfer
                            CpuSuspendIntr(&intStatus);

                            dmaID = sceSifSetDma(&dmaStruct, 1);

                            CpuResumeIntr(intStatus);

                            matched_entries++;
                        } else {
#ifdef DEBUG
                            printf("We found a file, but it didnt match the requested extension list\n");
#endif
                        }
                    } else  // no extension list to match against
                    {
#ifdef DEBUG
                        printf("We found a file, and there is not extension list to match against\n");
#endif

                        // DMA localTocEntry to the address specified by tocEntry[matched_entries]

                        // setup the dma struct
                        dmaStruct.src = &localTocEntry;
                        dmaStruct.dest = &tocEntry[matched_entries];
                        dmaStruct.size = sizeof(struct TocEntry);
                        dmaStruct.attr = 0;

                        // Do the DMA transfer
                        CpuSuspendIntr(&intStatus);

                        dmaID = sceSifSetDma(&dmaStruct, 1);

                        CpuResumeIntr(intStatus);

                        matched_entries++;
                    }
                }

                dir_entry++;

                if (matched_entries >= req_entries)  // if we've filled the requested buffer
                    return (matched_entries);        // then just return

            }  // end of the current cache block


            // if there is more dir to load, then load next chunk, else finish
            if ((CachedDirInfo.cache_offset + CachedDirInfo.cache_size) < CachedDirInfo.sector_num) {
                if (CDVD_Cache_Dir(CachedDirInfo.pathname, CACHE_NEXT) != TRUE) {
                    // failed to cache next block (should return TRUE even if
                    // there is no more directory, as long as a CD read didnt fail
                    return -1;
                }
            } else
                break;

            tocEntryPointer = (struct dirTocEntry *)CachedDirInfo.cache;
        }
    }
    // reached the end of the dir, before filling up the requested entries

    return (matched_entries);
}