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
typedef  int u32 ;
typedef  int /*<<< orphan*/  dough ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (int*,int*,int) ; 

__attribute__((used)) static void cookey(const u32 *raw1, u32 *keyout)
{
	u32 *cook;
	const u32 *raw0;
	u32 dough[32];
	int i;

	cook = dough;
	for (i = 0; i < 16; i++, raw1++) {
		raw0 = raw1++;
		*cook    = (*raw0 & 0x00fc0000L) << 6;
		*cook   |= (*raw0 & 0x00000fc0L) << 10;
		*cook   |= (*raw1 & 0x00fc0000L) >> 10;
		*cook++ |= (*raw1 & 0x00000fc0L) >> 6;
		*cook    = (*raw0 & 0x0003f000L) << 12;
		*cook   |= (*raw0 & 0x0000003fL) << 16;
		*cook   |= (*raw1 & 0x0003f000L) >> 4;
		*cook++ |= (*raw1 & 0x0000003fL);
	}

	os_memcpy(keyout, dough, sizeof(dough));
}