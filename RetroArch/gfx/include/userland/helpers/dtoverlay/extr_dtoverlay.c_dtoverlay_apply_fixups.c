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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ fixup_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  fdt; } ;
typedef  TYPE_1__ DTBLOB_T ;

/* Variables and functions */
 int FDT_ERR_BADSTRUCTURE ; 
 scalar_t__ FIXUP_RELATIVE ; 
 scalar_t__ dtoverlay_read_u32 (void const*,unsigned long) ; 
 int /*<<< orphan*/  dtoverlay_write_u32 (void*,unsigned long,scalar_t__) ; 
 void* fdt_getprop_namelen (int /*<<< orphan*/ ,int,char const*,int,int*) ; 
 int fdt_path_offset_namelen (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  phandle_debug (char*,char const*,scalar_t__,...) ; 
 char* strchr (char const*,char) ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static int dtoverlay_apply_fixups(DTBLOB_T *dtb, const char *fixups_stringlist,
                                  uint32_t phandle, fixup_type_t type)
{
   // The fixups arrive as a sequence of NUL-terminated strings, of the form:
   //   "path:property:offset"
   // Use an empty string as an end marker, since:
   // 1) all tags begin 0x00 0x00 0x00,
   // 2) all string properties must be followed by a tag,
   // 3) an empty string is not a valid fixup, and
   // 4) the code is simpler as a result.

   const char *fixup = fixups_stringlist;

   while  (fixup[0])
   {
      const char *prop_name, *offset_str;
      char *offset_end;
      const void *prop_ptr;
      int prop_len;
      int node_off;
      unsigned long offset;
      uint32_t patch;

      prop_name = strchr(fixup, ':');
      if (!prop_name)
         return -FDT_ERR_BADSTRUCTURE;
      prop_name++;

      offset_str = strchr(prop_name, ':');
      if (!offset_str)
         return -FDT_ERR_BADSTRUCTURE;
      offset_str++;

      offset = strtoul(offset_str, &offset_end, 10);
      if ((offset_end == offset_str) || (offset_end[0] != 0))
         return -FDT_ERR_BADSTRUCTURE;

      node_off = fdt_path_offset_namelen(dtb->fdt, fixup, prop_name - 1 - fixup);
      if (node_off < 0)
         return node_off;

      prop_ptr = fdt_getprop_namelen(dtb->fdt, node_off, prop_name,
                                     offset_str - 1 - prop_name, &prop_len);
      if (!prop_ptr)
         return prop_len;
      if (offset > (prop_len - 4))
         return -FDT_ERR_BADSTRUCTURE;

      // Now apply the patch. Yes, prop_ptr is a const void *, but the
      // alternative (copying the whole property, patching, then updating as
      // a whole) is ridiculous.
      if (type == FIXUP_RELATIVE)
      {
         patch = phandle + dtoverlay_read_u32(prop_ptr, offset);
         phandle_debug("  phandle fixup %d+%d->%d", phandle, patch - phandle, patch);
      }
      else
      {
         patch = phandle;
         phandle_debug("  phandle ref '%s'->%d", prop_name, patch);
      }

      dtoverlay_write_u32((void *)prop_ptr, offset, patch);

      fixup = offset_end + 1;
   }

   return 0;
}