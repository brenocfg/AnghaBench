#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  store_palette_entry ;
struct TYPE_6__ {TYPE_1__* current; int /*<<< orphan*/  pread; } ;
typedef  TYPE_2__ png_store ;
struct TYPE_5__ {int npalette; int /*<<< orphan*/ * palette; } ;

/* Variables and functions */
 int /*<<< orphan*/  store_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static store_palette_entry *
store_current_palette(png_store *ps, int *npalette)
{
   /* This is an internal error (the call has been made outside a read
    * operation.)
    */
   if (ps->current == NULL)
   {
      store_log(ps, ps->pread, "no current stream for palette", 1);
      return NULL;
   }

   /* The result may be null if there is no palette. */
   *npalette = ps->current->npalette;
   return ps->current->palette;
}