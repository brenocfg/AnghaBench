#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* joypad; } ;
typedef  TYPE_2__ xdk_input_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* destroy ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void xdk_input_free_input(void *data)
{
   xdk_input_t *xdk = (xdk_input_t*)data;

   if (!xdk)
      return;

   if (xdk->joypad)
      xdk->joypad->destroy();

   free(xdk);
}