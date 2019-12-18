#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dynstring {int size; int /*<<< orphan*/  buf; scalar_t__ len; } ;

/* Variables and functions */
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  dtoverlay_error (char*) ; 
 int /*<<< orphan*/  malloc (int) ; 

__attribute__((used)) static int dynstring_init_size(struct dynstring *ds, int initial_size)
{
   if (initial_size < 32)
      initial_size = 32;
   ds->size = initial_size;
   ds->len = 0;
   ds->buf = malloc(initial_size);
   if (!ds->buf)
   {
      dtoverlay_error("  out of memory");
      return -FDT_ERR_NOSPACE;
   }
   return 0;
}