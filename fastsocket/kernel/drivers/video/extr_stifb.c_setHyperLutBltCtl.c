#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bits_per_pixel; } ;
struct TYPE_7__ {TYPE_1__ var; } ;
struct stifb_info {TYPE_2__ info; } ;
struct TYPE_8__ {int length; int lutOffset; int /*<<< orphan*/  lutType; } ;
struct TYPE_9__ {int all; TYPE_3__ fields; } ;
typedef  TYPE_4__ NgleLutBltCtl ;

/* Variables and functions */
 int /*<<< orphan*/  HYPER_CMAP_TYPE ; 

__attribute__((used)) static NgleLutBltCtl
setHyperLutBltCtl(struct stifb_info *fb, int offsetWithinLut, int length) 
{
	NgleLutBltCtl lutBltCtl;

	/* set enable, zero reserved fields */
	lutBltCtl.all = 0x80000000;

	lutBltCtl.fields.length = length;
	lutBltCtl.fields.lutType = HYPER_CMAP_TYPE;

	/* Expect lutIndex to be 0 or 1 for image cmaps, 2 or 3 for overlay cmaps */
	if (fb->info.var.bits_per_pixel == 8)
		lutBltCtl.fields.lutOffset = 2 * 256;
	else
		lutBltCtl.fields.lutOffset = 0 * 256;

	/* Offset points to start of LUT.  Adjust for within LUT */
	lutBltCtl.fields.lutOffset += offsetWithinLut;

	return lutBltCtl;
}