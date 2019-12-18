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
struct TYPE_4__ {struct TYPE_4__* trailer; scalar_t__ trailer_is_malloced; struct TYPE_4__* fdt; scalar_t__ fdt_is_malloced; } ;
typedef  TYPE_1__ DTBLOB_T ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void dtoverlay_free_dtb(DTBLOB_T *dtb)
{
   if (dtb)
   {
      if (dtb->fdt_is_malloced)
         free(dtb->fdt);
      if (dtb->trailer_is_malloced)
         free(dtb->trailer);
      free(dtb);
   }
}