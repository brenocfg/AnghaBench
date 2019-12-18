#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void u8 ;
typedef  int const u32 ;

/* Variables and functions */
 int hCDROM ; 
 int /*<<< orphan*/  memcpy (void*,void*,int const) ; 
 scalar_t__ pread (int,void*,int const,int const) ; 

__attribute__((used)) static int MacOSXCDReadSectorFAD(u32 FAD, void *buffer) 
{
	const int blockSize = 2352;
#ifdef CRAB_REWRITE
    const int cacheBlocks = 32;
    static u8 cache[blockSize * cacheBlocks];
    static u32 cacheFAD = 0xFFFFFF00;
#endif
	
	if (hCDROM != -1) 
	{
#ifdef CRAB_REWRITE
        /* See if the block we are looking for is in the cache already... */
        if(FAD < cacheFAD || FAD >= cacheFAD + cacheBlocks) {
            /* Cache miss, read some blocks from the cd, then we'll hit the
               cache below. */
            if(!pread(hCDROM, cache, blockSize * cacheBlocks,
                      (FAD - 150) * blockSize)) {
                return 0;
            }

            cacheFAD = FAD;
        }

        /* Cache hit, copy the block out. */
        memcpy(buffer, cache + (blockSize * (FAD - cacheFAD)), blockSize);
        return 1;
#else
		if (pread(hCDROM, buffer, blockSize, (FAD - 150) * blockSize))
			return true;
#endif
	}
	
	return false;
}