#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int mctlwtst; } ;
struct TYPE_10__ {int system; } ;
struct TYPE_14__ {TYPE_6__ reg; TYPE_3__ pll; } ;
struct TYPE_11__ {int ref_freq; } ;
struct TYPE_12__ {TYPE_4__ pll; } ;
struct TYPE_8__ {unsigned int vcomax; } ;
struct TYPE_9__ {TYPE_1__ pixel; } ;
struct matrox_fb_info {TYPE_7__ values; TYPE_5__ features; TYPE_2__ limits; } ;
struct matrox_bios {int* pins; } ;

/* Variables and functions */
 int get_unaligned_le16 (int*) ; 

__attribute__((used)) static int parse_pins1(struct matrox_fb_info *minfo,
		       const struct matrox_bios *bd)
{
	unsigned int maxdac;

	switch (bd->pins[22]) {
		case 0:		maxdac = 175000; break;
		case 1:		maxdac = 220000; break;
		default:	maxdac = 240000; break;
	}
	if (get_unaligned_le16(bd->pins + 24)) {
		maxdac = get_unaligned_le16(bd->pins + 24) * 10;
	}
	minfo->limits.pixel.vcomax = maxdac;
	minfo->values.pll.system = get_unaligned_le16(bd->pins + 28) ?
		get_unaligned_le16(bd->pins + 28) * 10 : 50000;
	/* ignore 4MB, 8MB, module clocks */
	minfo->features.pll.ref_freq = 14318;
	minfo->values.reg.mctlwtst	= 0x00030101;
	return 0;
}