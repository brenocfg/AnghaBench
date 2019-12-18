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
 int* VRAM_CACHED_STUFF ; 
 int /*<<< orphan*/  memset32 (int*,int,int) ; 
 int /*<<< orphan*/  memset32_uncached (int*,int /*<<< orphan*/ ,int) ; 
 int* psp_screen ; 
 int /*<<< orphan*/  psp_video_flip (int /*<<< orphan*/ ) ; 
 void* psp_video_get_active_fb () ; 

__attribute__((used)) static void clearArea(int full)
{
	if (full) {
		memset32_uncached(psp_screen, 0, 512*272*2/4);
		psp_video_flip(0);
		memset32_uncached(psp_screen, 0, 512*272*2/4);
		memset32(VRAM_CACHED_STUFF, 0xe0e0e0e0, 512*240/4);
		memset32((int *)VRAM_CACHED_STUFF+512*240/4, 0, 512*240*2/4);
	} else {
		void *fb = psp_video_get_active_fb();
		memset32_uncached((int *)((char *)psp_screen + 512*264*2), 0, 512*8*2/4);
		memset32_uncached((int *)((char *)fb         + 512*264*2), 0, 512*8*2/4);
	}
}