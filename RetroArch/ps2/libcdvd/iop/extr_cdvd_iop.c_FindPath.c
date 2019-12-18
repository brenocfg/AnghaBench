#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dirTocEntry {int length; int fileProperties; } ;
struct TocEntry {int fileLBA; int fileSize; int /*<<< orphan*/  filename; } ;
struct TYPE_4__ {int tocSize; } ;
struct TYPE_6__ {TYPE_1__ rootToc; } ;
struct TYPE_5__ {char* cache; int cache_size; int cache_offset; int sector_num; int sector_start; int valid; scalar_t__ path_depth; scalar_t__* pathname; } ;

/* Variables and functions */
 TYPE_3__ CDVolDesc ; 
 TYPE_2__ CachedDirInfo ; 
 int FALSE ; 
 void* MAX_DIR_CACHE_SECTORS ; 
 int ReadSect (int,void*,char*,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  TocEntryCopy (struct TocEntry*,struct dirTocEntry*) ; 
 int /*<<< orphan*/  cdReadMode ; 
 int /*<<< orphan*/  isValidDisc () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sceCdDiskReady (int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (scalar_t__*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 char* strrchr (scalar_t__*,char) ; 
 char* strtok (char*,char*) ; 

int FindPath(char *pathname)
{
    char *dirname;
    char *seperator;

    int dir_entry;
    int found_dir;

    struct dirTocEntry *tocEntryPointer;
    struct TocEntry localTocEntry;

    dirname = strtok(pathname, "\\/");

#ifdef DEBUG
    printf("FindPath: trying to find directory %s\n", pathname);
#endif

    if (!isValidDisc())
        return FALSE;

    sceCdDiskReady(0);

    while (dirname != NULL) {
        found_dir = FALSE;

        tocEntryPointer = (struct dirTocEntry *)CachedDirInfo.cache;

        // Always skip the first entry (self-refencing entry)
        tocEntryPointer = (struct dirTocEntry *)((u8 *)tocEntryPointer + tocEntryPointer->length);

        dir_entry = 0;

        for (; tocEntryPointer < (struct dirTocEntry *)(CachedDirInfo.cache + (CachedDirInfo.cache_size * 2048)); tocEntryPointer = (struct dirTocEntry *)((u8 *)tocEntryPointer + tocEntryPointer->length)) {
            // If we have a null toc entry, then we've either reached the end of the dir, or have reached a sector boundary
            if (tocEntryPointer->length == 0) {
#ifdef DEBUG
                printf("Got a null pointer entry, so either reached end of dir, or end of sector\n");
#endif

                tocEntryPointer = (struct dirTocEntry *)(CachedDirInfo.cache + (((((char *)tocEntryPointer - CachedDirInfo.cache) / 2048) + 1) * 2048));
            }

            if (tocEntryPointer >= (struct dirTocEntry *)(CachedDirInfo.cache + (CachedDirInfo.cache_size * 2048))) {
                // If we've gone past the end of the cache
                // then check if there are more sectors to load into the cache

                if ((CachedDirInfo.cache_offset + CachedDirInfo.cache_size) < CachedDirInfo.sector_num) {
                    // If there are more sectors to load, then load them
                    CachedDirInfo.cache_offset += CachedDirInfo.cache_size;
                    CachedDirInfo.cache_size = CachedDirInfo.sector_num - CachedDirInfo.cache_offset;

                    if (CachedDirInfo.cache_size > MAX_DIR_CACHE_SECTORS)
                        CachedDirInfo.cache_size = MAX_DIR_CACHE_SECTORS;

                    if (ReadSect(CachedDirInfo.sector_start + CachedDirInfo.cache_offset, CachedDirInfo.cache_size, CachedDirInfo.cache, &cdReadMode) != TRUE) {
#ifdef DEBUG
                        printf("Couldn't Read from CD !\n");
#endif

                        CachedDirInfo.valid = FALSE;  // should we completely invalidate just because we couldnt read time?
                        return FALSE;
                    }

                    tocEntryPointer = (struct dirTocEntry *)CachedDirInfo.cache;
                } else {
                    CachedDirInfo.valid = FALSE;
                    return FALSE;
                }
            }

            // If the toc Entry is a directory ...
            if (tocEntryPointer->fileProperties & 0x02) {
                // Convert to our format (inc ascii name), for the check
                TocEntryCopy(&localTocEntry, tocEntryPointer);

                // If it's the link to the parent directory, then give it the name ".."
                if (dir_entry == 0) {
                    if (CachedDirInfo.path_depth != 0) {
#ifdef DEBUG
                        printf("First directory entry in dir, so name it '..'\n");
#endif

                        strcpy(localTocEntry.filename, "..");
                    }
                }

                // Check if this is the directory that we are looking for
                if (strcasecmp(dirname, localTocEntry.filename) == 0) {
#ifdef DEBUG
                    printf("Found the matching sub-directory\n");
#endif

                    found_dir = TRUE;

                    if (dir_entry == 0) {
                        // We've matched with the parent directory
                        // so truncate the pathname by one level

                        if (CachedDirInfo.path_depth > 0)
                            CachedDirInfo.path_depth--;

                        if (CachedDirInfo.path_depth == 0) {
                            // If at root then just clear the path to root
                            // (simpler than finding the colon seperator etc)
                            CachedDirInfo.pathname[0] = 0;
                        } else {
                            seperator = strrchr(CachedDirInfo.pathname, '/');

                            if (seperator != NULL)
                                *seperator = 0;
                        }
                    } else {
                        // otherwise append a seperator, and the matched directory
                        // to the pathname
                        strcat(CachedDirInfo.pathname, "/");

#ifdef DEBUG
                        printf("Adding '%s' to cached pathname - path depth = %d\n", dirname, CachedDirInfo.path_depth);
#endif

                        strcat(CachedDirInfo.pathname, dirname);

                        CachedDirInfo.path_depth++;
                    }

                    // Exit out of the search loop
                    // (and find the next sub-directory, if there is one)
                    break;
                } else {
#ifdef DEBUG
                    printf("Found a directory, but it doesn't match\n");
#endif
                }
            }

            dir_entry++;

        }  // end of cache block search loop


        // if we've reached here, without finding the directory, then it's not there
        if (found_dir != TRUE) {
            CachedDirInfo.valid = FALSE;
            return FALSE;
        }

        // find name of next dir
        dirname = strtok(NULL, "\\/");

        CachedDirInfo.sector_start = localTocEntry.fileLBA;
        CachedDirInfo.sector_num = (localTocEntry.fileSize >> 11) + ((CDVolDesc.rootToc.tocSize & 2047) != 0);

        // Cache the start of the found directory
        // (used in searching if this isn't the last dir,
        // or used by whatever requested the cache in the first place if it is the last dir)
        CachedDirInfo.cache_offset = 0;
        CachedDirInfo.cache_size = CachedDirInfo.sector_num;

        if (CachedDirInfo.cache_size > MAX_DIR_CACHE_SECTORS)
            CachedDirInfo.cache_size = MAX_DIR_CACHE_SECTORS;

        if (ReadSect(CachedDirInfo.sector_start + CachedDirInfo.cache_offset, CachedDirInfo.cache_size, CachedDirInfo.cache, &cdReadMode) != TRUE) {
#ifdef DEBUG
            printf("Couldn't Read from CD, trying to read %d sectors, starting at sector %d !\n",
                   CachedDirInfo.cache_size, CachedDirInfo.sector_start + CachedDirInfo.cache_offset);
#endif

            CachedDirInfo.valid = FALSE;  // should we completely invalidate just because we couldnt read time?
            return FALSE;
        }
    }

// If we've got here then we found the requested directory
#ifdef DEBUG
    printf("FindPath found the path\n");
#endif

    CachedDirInfo.valid = TRUE;
    return TRUE;
}