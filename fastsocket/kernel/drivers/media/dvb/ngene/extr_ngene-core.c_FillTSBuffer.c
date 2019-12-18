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

/* Variables and functions */
 int DF_SWAP32 ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 

void FillTSBuffer(void *Buffer, int Length, u32 Flags)
{
	u32 *ptr = Buffer;

	memset(Buffer, 0xff, Length);
	while (Length > 0) {
		if (Flags & DF_SWAP32)
			*ptr = 0x471FFF10;
		else
			*ptr = 0x10FF1F47;
		ptr += (188 / 4);
		Length -= 188;
	}
}