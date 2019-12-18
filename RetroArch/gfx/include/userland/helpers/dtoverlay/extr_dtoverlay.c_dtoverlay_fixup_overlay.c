#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fixups_applied; } ;
typedef  TYPE_1__ DTBLOB_T ;

/* Variables and functions */
 int NON_FATAL (int) ; 
 int dtoverlay_resolve_fixups (TYPE_1__*,TYPE_1__*) ; 
 int dtoverlay_resolve_phandles (TYPE_1__*,TYPE_1__*) ; 

int dtoverlay_fixup_overlay(DTBLOB_T *base_dtb, DTBLOB_T *overlay_dtb)
{
   int err;

   // To do: Check the "compatible" string?

   err = dtoverlay_resolve_fixups(base_dtb, overlay_dtb);

   if (err >= 0)
      err = dtoverlay_resolve_phandles(base_dtb, overlay_dtb);

   overlay_dtb->fixups_applied = 1;

   return NON_FATAL(err);
}