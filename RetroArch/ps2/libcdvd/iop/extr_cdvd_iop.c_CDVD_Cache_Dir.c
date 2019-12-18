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
typedef  enum Cache_getMode { ____Placeholder_Cache_getMode } Cache_getMode ;
struct TYPE_4__ {scalar_t__ tocLBA; int tocSize; } ;
struct TYPE_6__ {TYPE_1__ rootToc; } ;
struct TYPE_5__ {scalar_t__ valid; scalar_t__ cache_offset; void* cache_size; void* sector_num; scalar_t__ sector_start; char* pathname; int /*<<< orphan*/  cache; scalar_t__ path_depth; } ;

/* Variables and functions */
 int CACHE_START ; 
 scalar_t__ CDVD_GetVolumeDescriptor () ; 
 TYPE_3__ CDVolDesc ; 
 TYPE_2__ CachedDirInfo ; 
 scalar_t__ ComparePath (char const*) ; 
 int FALSE ; 
 int FindPath (char*) ; 
 scalar_t__ MATCH ; 
 void* MAX_DIR_CACHE_SECTORS ; 
 scalar_t__ ReadSect (scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SUBDIR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  cdReadMode ; 
 int /*<<< orphan*/  isValidDisc () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sceCdDiskReady (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char*) ; 

int CDVD_Cache_Dir(const char *pathname, enum Cache_getMode getMode)
{

    // macke sure that the requested pathname is not directly modified
    static char dirname[1024];

    int path_len;

#ifdef DEBUG
    printf("Attempting to find, and cache, directory: %s\n", pathname);
#endif

    // only take any notice of the existing cache, if it's valid
    if (CachedDirInfo.valid == TRUE) {
        // Check if the requested path is already cached
        //		if (strcasecmp(pathname,CachedDirInfo.pathname)==0)
        if (ComparePath(pathname) == MATCH) {
#ifdef DEBUG
            printf("CacheDir: The requested path is already cached\n");
#endif

            // If so, is the request ot cache the start of the directory, or to resume the next block ?
            if (getMode == CACHE_START) {
#ifdef DEBUG
                printf("          and requested cache from start of dir\n");
#endif

                if (CachedDirInfo.cache_offset == 0) {
// requested cache of start of the directory, and thats what's already cached
// so sit back and do nothing
#ifdef DEBUG
                    printf("          and start of dir is already cached so nothing to do :o)\n");
#endif

                    CachedDirInfo.valid = TRUE;
                    return TRUE;
                } else {
// Requested cache of start of the directory, but thats not what's cached
// so re-cache the start of the directory

#ifdef DEBUG
                    printf("          but dir isn't cached from start, so re-cache existing dir from start\n");
#endif

                    // reset cache data to start of existing directory
                    CachedDirInfo.cache_offset = 0;
                    CachedDirInfo.cache_size = CachedDirInfo.sector_num;

                    if (CachedDirInfo.cache_size > MAX_DIR_CACHE_SECTORS)
                        CachedDirInfo.cache_size = MAX_DIR_CACHE_SECTORS;

                    // Now fill the cache with the specified sectors
                    if (ReadSect(CachedDirInfo.sector_start + CachedDirInfo.cache_offset, CachedDirInfo.cache_size, CachedDirInfo.cache, &cdReadMode) != TRUE) {
#ifdef DEBUG
                        printf("Couldn't Read from CD !\n");
#endif

                        CachedDirInfo.valid = FALSE;  // should we completely invalidate just because we couldnt read first time?
                        return FALSE;
                    }

                    CachedDirInfo.valid = TRUE;
                    return TRUE;
                }
            } else  // getMode == CACHE_NEXT
            {
                // So get the next block of the existing directory

                CachedDirInfo.cache_offset += CachedDirInfo.cache_size;

                CachedDirInfo.cache_size = CachedDirInfo.sector_num - CachedDirInfo.cache_offset;

                if (CachedDirInfo.cache_size > MAX_DIR_CACHE_SECTORS)
                    CachedDirInfo.cache_size = MAX_DIR_CACHE_SECTORS;

                // Now fill the cache with the specified sectors
                if (ReadSect(CachedDirInfo.sector_start + CachedDirInfo.cache_offset, CachedDirInfo.cache_size, CachedDirInfo.cache, &cdReadMode) != TRUE) {
#ifdef DEBUG
                    printf("Couldn't Read from CD !\n");
#endif

                    CachedDirInfo.valid = FALSE;  // should we completely invalidate just because we couldnt read first time?
                    return FALSE;
                }

                CachedDirInfo.valid = TRUE;
                return TRUE;
            }
        } else  // requested directory is not the cached directory (but cache is still valid)
        {
#ifdef DEBUG
            printf("Cache is valid, but cached directory, is not the requested one\n"
                   "so check if the requested directory is a sub-dir of the cached one\n");

            printf("Requested Path = %s , Cached Path = %s\n", pathname, CachedDirInfo.pathname);
#endif


            // Is the requested pathname a sub-directory of the current-directory ?

            // if the requested pathname is longer than the pathname of the cached dir
            // and the pathname of the cached dir matches the beginning of the requested pathname
            // and the next character in the requested pathname is a dir seperator
            //			printf("Length of Cached pathname = %d, length of req'd pathname = %d\n",path_len, strlen(pathname));
            //			printf("Result of strncasecmp = %d\n",strncasecmp(pathname, CachedDirInfo.pathname, path_len));
            //			printf("next character after length of cached name = %c\n",pathname[path_len]);

            //			if ((strlen(pathname) > path_len)
            //				&& (strncasecmp(pathname, CachedDirInfo.pathname, path_len)==0)
            //				&& ((pathname[path_len]=='/') || (pathname[path_len]=='\\')))

            if (ComparePath(pathname) == SUBDIR) {
// If so then we can start our search for the path, from the currently cached directory
#ifdef DEBUG
                printf("Requested dir is a sub-dir of the cached directory,\n"
                       "so start search from current cached dir\n");
#endif
                // if the cached chunk, is not the start of the dir,
                // then we will need to re-load it before starting search
                if (CachedDirInfo.cache_offset != 0) {
                    CachedDirInfo.cache_offset = 0;
                    CachedDirInfo.cache_size = CachedDirInfo.sector_num;
                    if (CachedDirInfo.cache_size > MAX_DIR_CACHE_SECTORS)
                        CachedDirInfo.cache_size = MAX_DIR_CACHE_SECTORS;

                    // Now fill the cache with the specified sectors
                    if (ReadSect(CachedDirInfo.sector_start + CachedDirInfo.cache_offset, CachedDirInfo.cache_size, CachedDirInfo.cache, &cdReadMode) != TRUE) {
#ifdef DEBUG
                        printf("Couldn't Read from CD !\n");
#endif

                        CachedDirInfo.valid = FALSE;  // should we completely invalidate just because we couldnt read time?
                        return FALSE;
                    }
                }

                // start the search, with the path after the current directory
                path_len = strlen(CachedDirInfo.pathname);
                strcpy(dirname, pathname + path_len);

                // FindPath should use the current directory cache to start it's search
                // and should change CachedDirInfo.pathname, to the path of the dir it finds
                // it should also cache the first chunk of directory sectors,
                // and fill the contents of the other elements of CachedDirInfo appropriately

                return (FindPath(dirname));
            }
        }
    }

// If we've got here, then either the cache was not valid to start with
// or the requested path is not a subdirectory of the currently cached directory
// so lets start again
#ifdef DEBUG
    printf("The cache is not valid, or the requested directory is not a sub-dir of the cached one\n");
#endif

    if (!isValidDisc()) {
#ifdef DEBUG
        printf("No supported disc inserted.\n");
#endif

        return -1;
    }

    sceCdDiskReady(0);

    // Read the main volume descriptor
    if (CDVD_GetVolumeDescriptor() != TRUE) {
#ifdef DEBUG
        printf("Could not read the CD/DVD Volume Descriptor\n");
#endif

        return -1;
    }

#ifdef DEBUG
    printf("Read the CD Volume Descriptor\n");
#endif

    CachedDirInfo.path_depth = 0;

    strcpy(CachedDirInfo.pathname, "");

    // Setup the lba and sector size, for retrieving the root toc
    CachedDirInfo.cache_offset = 0;
    CachedDirInfo.sector_start = CDVolDesc.rootToc.tocLBA;
    CachedDirInfo.sector_num = (CDVolDesc.rootToc.tocSize >> 11) + ((CDVolDesc.rootToc.tocSize & 2047) != 0);

    CachedDirInfo.cache_size = CachedDirInfo.sector_num;

    if (CachedDirInfo.cache_size > MAX_DIR_CACHE_SECTORS)
        CachedDirInfo.cache_size = MAX_DIR_CACHE_SECTORS;


    // Now fill the cache with the specified sectors
    if (ReadSect(CachedDirInfo.sector_start + CachedDirInfo.cache_offset, CachedDirInfo.cache_size, CachedDirInfo.cache, &cdReadMode) != TRUE) {
#ifdef DEBUG
        printf("Couldn't Read from CD !\n");
#endif

        CachedDirInfo.valid = FALSE;  // should we completely invalidate just because we couldnt read time?
        return FALSE;
    }

#ifdef DEBUG
    printf("Read the first block from the root directory\n");
#endif

// FindPath should use the current directory cache to start it's search (in this case the root)
// and should change CachedDirInfo.pathname, to the path of the dir it finds
// it should also cache the first chunk of directory sectors,
// and fill the contents of the other elements of CachedDirInfo appropriately
#ifdef DEBUG
    printf("Calling FindPath\n");
#endif
    strcpy(dirname, pathname);

    return (FindPath(dirname));
}