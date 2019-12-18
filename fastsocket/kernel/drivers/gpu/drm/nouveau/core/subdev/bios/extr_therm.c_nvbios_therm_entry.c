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
typedef  int u8 ;
typedef  int u16 ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int therm_table (struct nouveau_bios*,int*,int*,int*,int*) ; 

__attribute__((used)) static u16
nvbios_therm_entry(struct nouveau_bios *bios, int idx, u8 *ver, u8 *len)
{
	u8 hdr, cnt;
	u16 therm = therm_table(bios, ver, &hdr, len, &cnt);
	if (therm && idx < cnt)
		return therm + idx * *len;
	return 0x0000;
}