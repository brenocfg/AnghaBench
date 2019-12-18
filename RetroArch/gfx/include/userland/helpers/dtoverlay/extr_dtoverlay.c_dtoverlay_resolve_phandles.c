#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  max_phandle; int /*<<< orphan*/  fdt; } ;
typedef  TYPE_1__ DTBLOB_T ;

/* Variables and functions */
 int /*<<< orphan*/  FIXUP_RELATIVE ; 
 int dtoverlay_apply_fixups (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dtoverlay_apply_fixups_node (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtoverlay_error (char*) ; 
 int /*<<< orphan*/  dtoverlay_phandle_relocate (TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 
 char* fdt_getprop (int /*<<< orphan*/ ,int,char*,int*) ; 
 int fdt_next_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int fdt_path_offset (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  phandle_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dtoverlay_resolve_phandles(DTBLOB_T *base_dtb, DTBLOB_T *overlay_dtb)
{
   int local_fixups_off;
   int node_off;
   int err = 0;

   // First find and update the phandles in the overlay

   for (node_off = 0;
        node_off >= 0;
        node_off = fdt_next_node(overlay_dtb->fdt, node_off, NULL))
   {
      dtoverlay_phandle_relocate(overlay_dtb, node_off, "phandle",
                                 base_dtb->max_phandle);
      dtoverlay_phandle_relocate(overlay_dtb, node_off, "linux,phandle",
                                 base_dtb->max_phandle);
   }

   local_fixups_off = fdt_path_offset(overlay_dtb->fdt, "/__local_fixups__");
   if (local_fixups_off >= 0)
   {
      const char *fixups_stringlist;

      // Update the references to local phandles using the local fixups.
      // The property name is "fixup".
      // The value is a NUL-separated stringlist of descriptors of the form:
      //    path:property:offset
      fixups_stringlist =
         fdt_getprop(overlay_dtb->fdt, local_fixups_off, "fixup", &err);
      if (fixups_stringlist)
      {
         // Relocate the overlay phandle references
         err = dtoverlay_apply_fixups(overlay_dtb, fixups_stringlist,
                                      base_dtb->max_phandle, FIXUP_RELATIVE);
      }
      else
      {
          err = dtoverlay_apply_fixups_node(overlay_dtb, local_fixups_off,
                                            0, base_dtb->max_phandle);
      }
      if (err < 0)
      {
         dtoverlay_error("error applying local fixups");
         return err;
      }
   }

   overlay_dtb->max_phandle += base_dtb->max_phandle;
   phandle_debug("  +overlay max phandle +%d -> %d", base_dtb->max_phandle, overlay_dtb->max_phandle);

   return err;
}