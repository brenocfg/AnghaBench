#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int ref_freq; } ;
struct TYPE_13__ {TYPE_4__ pll; } ;
struct TYPE_10__ {int system; } ;
struct TYPE_9__ {int mctlwtst; int memrdbk; int opt; int opt3; } ;
struct TYPE_11__ {TYPE_2__ pll; TYPE_1__ reg; } ;
struct TYPE_15__ {int vcomax; } ;
struct TYPE_14__ {int vcomax; } ;
struct TYPE_16__ {TYPE_7__ system; TYPE_6__ pixel; } ;
struct matrox_fb_info {TYPE_5__ features; TYPE_3__ values; TYPE_8__ limits; } ;

/* Variables and functions */

__attribute__((used)) static void default_pins4(struct matrox_fb_info *minfo)
{
	/* G400 */
	minfo->limits.pixel.vcomax	=
	minfo->limits.system.vcomax	= 252000;
	minfo->values.reg.mctlwtst	= 0x04A450A1;
	minfo->values.reg.memrdbk	= 0x000000E7;
	minfo->values.reg.opt		= 0x10000400;
	minfo->values.reg.opt3		= 0x0190A419;
	minfo->values.pll.system	= 200000;
	minfo->features.pll.ref_freq	= 27000;
}