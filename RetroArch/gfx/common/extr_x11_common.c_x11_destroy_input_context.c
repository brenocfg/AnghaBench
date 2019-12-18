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
typedef  int /*<<< orphan*/ * XIM ;
typedef  int /*<<< orphan*/ * XIC ;

/* Variables and functions */
 int /*<<< orphan*/  XCloseIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDestroyIC (int /*<<< orphan*/ *) ; 

void x11_destroy_input_context(XIM *xim, XIC *xic)
{
   if (*xic)
   {
      XDestroyIC(*xic);
      *xic = NULL;
   }

   if (*xim)
   {
      XCloseIM(*xim);
      *xim = NULL;
   }
}