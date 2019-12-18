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
struct dynstring {int size; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  dtoverlay_error (char*) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dynstring_set_size(struct dynstring *ds, int size)
{
   if (size > ds->size)
   {
      size = (size * 5)/4; // Add a 25% headroom
      ds->buf = realloc(ds->buf, size);
      if (!ds->buf)
      {
         dtoverlay_error("  out of memory");
         return -FDT_ERR_NOSPACE;
      }
      ds->size = size;
   }
   return 0;
}