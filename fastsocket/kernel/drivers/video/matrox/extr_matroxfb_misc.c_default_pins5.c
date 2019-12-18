#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int opt; int opt2; int opt3; int mctlwtst_core; int mctlwtst; int memmisc; int memrdbk; int maccess; } ;
struct TYPE_19__ {int ddr; int dll; int emrswen; } ;
struct TYPE_16__ {int system; int video; } ;
struct TYPE_11__ {TYPE_9__ reg; TYPE_8__ memory; TYPE_5__ pll; } ;
struct TYPE_17__ {int ref_freq; } ;
struct TYPE_18__ {TYPE_6__ pll; } ;
struct TYPE_14__ {int vcomax; int vcomin; } ;
struct TYPE_13__ {int vcomax; int vcomin; } ;
struct TYPE_12__ {int vcomax; int vcomin; } ;
struct TYPE_15__ {TYPE_3__ video; TYPE_2__ system; TYPE_1__ pixel; } ;
struct matrox_fb_info {TYPE_10__ values; TYPE_7__ features; TYPE_4__ limits; } ;

/* Variables and functions */

__attribute__((used)) static void default_pins5(struct matrox_fb_info *minfo)
{
	/* Mine 16MB G450 with SDRAM DDR */
	minfo->limits.pixel.vcomax	=
	minfo->limits.system.vcomax	=
	minfo->limits.video.vcomax	= 600000;
	minfo->limits.pixel.vcomin	=
	minfo->limits.system.vcomin	=
	minfo->limits.video.vcomin	= 256000;
	minfo->values.pll.system	=
	minfo->values.pll.video		= 284000;
	minfo->values.reg.opt		= 0x404A1160;
	minfo->values.reg.opt2		= 0x0000AC00;
	minfo->values.reg.opt3		= 0x0090A409;
	minfo->values.reg.mctlwtst_core	=
	minfo->values.reg.mctlwtst	= 0x0C81462B;
	minfo->values.reg.memmisc	= 0x80000004;
	minfo->values.reg.memrdbk	= 0x01001103;
	minfo->features.pll.ref_freq	= 27000;
	minfo->values.memory.ddr	= 1;
	minfo->values.memory.dll	= 1;
	minfo->values.memory.emrswen	= 1;
	minfo->values.reg.maccess	= 0x00004000;
}