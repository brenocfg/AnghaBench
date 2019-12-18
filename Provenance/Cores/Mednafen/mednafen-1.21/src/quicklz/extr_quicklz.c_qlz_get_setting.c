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

/* Variables and functions */
 int QLZ_COMPRESSION_LEVEL ; 
 int QLZ_SCRATCH_COMPRESS ; 
 int QLZ_SCRATCH_DECOMPRESS ; 
 int QLZ_STREAMING_MODE_VALUE ; 
 int QLZ_VERSION_MAJOR ; 
 int QLZ_VERSION_MINOR ; 
 int QLZ_VERSION_REVISION ; 

int qlz_get_setting(int setting)
{
	switch (setting)
	{
		case 0: return QLZ_COMPRESSION_LEVEL;
		case 1: return QLZ_SCRATCH_COMPRESS;
		case 2: return QLZ_SCRATCH_DECOMPRESS;
		case 3: return QLZ_STREAMING_MODE_VALUE;
#ifdef test_rle
		case 4: return 1;
#else
		case 4: return 0;
#endif
#ifdef speedup_incompressible
		case 5: return 1;
#else
		case 5: return 0;
#endif
#ifdef memory_safe
		case 6: return 1;
#else
		case 6: return 0;
#endif
		case 7: return QLZ_VERSION_MAJOR;
		case 8: return QLZ_VERSION_MINOR;
		case 9: return QLZ_VERSION_REVISION;
	}
	return -1;
}