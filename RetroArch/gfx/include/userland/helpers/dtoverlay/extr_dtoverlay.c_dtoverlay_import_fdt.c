#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ max_phandle; void* fdt; } ;
typedef  TYPE_1__ DTBLOB_T ;

/* Variables and functions */
 int FDT_ERR_NOSPACE ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  dtoverlay_error (char*,...) ; 
 int fdt_check_header (void*) ; 
 scalar_t__ fdt_get_phandle (void*,int) ; 
 int fdt_next_node (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdt_set_totalsize (void*,int) ; 
 int fdt_totalsize (void*) ; 

DTBLOB_T *dtoverlay_import_fdt(void *fdt, int buf_size)
{
   DTBLOB_T *dtb = NULL;
   int node_off;
   int dtb_len;
   int err;

   err = fdt_check_header(fdt);
   if (err != 0)
   {
      dtoverlay_error("not a valid FDT - err %d", err);
      goto error_exit;
   }

   dtb_len = fdt_totalsize(fdt);

   if (buf_size < dtb_len)
   {
      dtoverlay_error("fdt is too large");
      err = -FDT_ERR_NOSPACE;
      goto error_exit;
   }

   if (buf_size > dtb_len)
         fdt_set_totalsize(fdt, buf_size);

   dtb = calloc(1, sizeof(DTBLOB_T));
   if (!dtb)
   {
      dtoverlay_error("out of memory");
      goto error_exit;
   }

   dtb->fdt = fdt;
   dtb->max_phandle = 0; // Not a valid phandle

   // Find the minimum and maximum phandles, in case it is necessary to
   // relocate existing ones or create new ones.

   for (node_off = 0;
        node_off >= 0;
        node_off = fdt_next_node(fdt, node_off, NULL))
   {
      uint32_t phandle = fdt_get_phandle(fdt, node_off);
      if (phandle > dtb->max_phandle)
         dtb->max_phandle = phandle;
   }

error_exit:
   return dtb;
}