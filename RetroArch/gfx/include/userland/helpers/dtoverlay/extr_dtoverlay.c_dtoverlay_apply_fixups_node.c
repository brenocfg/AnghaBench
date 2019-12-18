#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  fdt; } ;
typedef  TYPE_1__ DTBLOB_T ;

/* Variables and functions */
 int FDT_ERR_BADSTRUCTURE ; 
 int FDT_ERR_INTERNAL ; 
 int dtoverlay_read_u32 (void*,int) ; 
 int /*<<< orphan*/  dtoverlay_write_u32 (void*,int,int) ; 
 int fdt_first_property_offset (int /*<<< orphan*/ ,int) ; 
 int fdt_first_subnode (int /*<<< orphan*/ ,int) ; 
 char* fdt_get_name (int /*<<< orphan*/ ,int,int*) ; 
 void* fdt_getprop_by_offset (int /*<<< orphan*/ ,int,char const**,int*) ; 
 void* fdt_getprop_w (int /*<<< orphan*/ ,int,char const*,int*) ; 
 int fdt_next_property_offset (int /*<<< orphan*/ ,int) ; 
 int fdt_next_subnode (int /*<<< orphan*/ ,int) ; 
 int fdt_subnode_offset_namelen (int /*<<< orphan*/ ,int,char const*,int) ; 
 int /*<<< orphan*/  phandle_debug (char*,int,int,int) ; 

__attribute__((used)) static int dtoverlay_apply_fixups_node(DTBLOB_T *dtb, int fix_off,
                                       int target_off, uint32_t phandle_offset)
{
   // The fixups are arranged as a subtree mirroring the structure of the
   // overall tree. Walk this tree in order. Each property is an array of cells
   // containing offsets to patch within the corresponding node/property of
   // the target tree.
   int err = 0;
   int prop_off;
   int subfix_off;

   // Merge each property of the node
   for (prop_off = fdt_first_property_offset(dtb->fdt, fix_off);
        (prop_off >= 0) && (err == 0);
        prop_off = fdt_next_property_offset(dtb->fdt, prop_off))
   {
      const char *prop_name;
      const void *prop_val;
      int prop_len;
      void *target_ptr;
      int target_len;
      int off;

      prop_val = fdt_getprop_by_offset(dtb->fdt, prop_off,
                                       &prop_name, &prop_len);
      if (!prop_val)
         return -FDT_ERR_INTERNAL;

      target_ptr = fdt_getprop_w(dtb->fdt, target_off, prop_name, &target_len);
      if (!target_ptr)
         return -FDT_ERR_BADSTRUCTURE;

      for (off = 0; (off + 4) <= prop_len; off += 4)
      {
         uint32_t patch;
         int patch_offset = dtoverlay_read_u32(prop_val, off);
         if ((patch_offset + 4) > target_len)
            return -FDT_ERR_BADSTRUCTURE;

         patch = phandle_offset + dtoverlay_read_u32(target_ptr, patch_offset);
         phandle_debug("  phandle fixup %d+%d->%d", phandle_offset, patch - phandle_offset, patch);

         dtoverlay_write_u32(target_ptr, patch_offset, patch);
      }
   }

   // Merge each subnode of the node
   for (subfix_off = fdt_first_subnode(dtb->fdt, fix_off);
        (subfix_off >= 0) && (err == 0);
        subfix_off = fdt_next_subnode(dtb->fdt, subfix_off))
   {
      const char *subnode_name;
      int name_len;
      int subtarget_off;

      subnode_name = fdt_get_name(dtb->fdt, subfix_off, &name_len);

      subtarget_off = fdt_subnode_offset_namelen(dtb->fdt, target_off,
                                                 subnode_name, name_len);

      if (subtarget_off >= 0)
      {
         err = dtoverlay_apply_fixups_node(dtb, subfix_off, subtarget_off,
                                           phandle_offset);
      }
      else
      {
         err = subtarget_off;
      }
   }

   return err;
}