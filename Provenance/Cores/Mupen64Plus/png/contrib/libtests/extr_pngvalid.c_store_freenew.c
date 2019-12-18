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
struct TYPE_3__ {int chunkpos; int chunklen; scalar_t__ npalette; int /*<<< orphan*/ * palette; scalar_t__ IDAT_bits; scalar_t__ IDAT_size; scalar_t__ chunktype; scalar_t__ writepos; int /*<<< orphan*/  new; } ;
typedef  TYPE_1__ png_store ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_freebuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
store_freenew(png_store *ps)
{
   store_freebuffer(&ps->new);
   ps->writepos = 0;
   ps->chunkpos = 8;
   ps->chunktype = 0;
   ps->chunklen = 16;
   ps->IDAT_size = 0;
   ps->IDAT_bits = 0;
   if (ps->palette != NULL)
   {
      free(ps->palette);
      ps->palette = NULL;
      ps->npalette = 0;
   }
}