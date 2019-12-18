#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mice_connected; TYPE_1__* joypad; } ;
typedef  TYPE_2__ ps3_input_t ;
struct TYPE_7__ {int /*<<< orphan*/  now_connect; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* poll ) () ;} ;
typedef  TYPE_3__ CellMouseInfo ;

/* Variables and functions */
 int /*<<< orphan*/  cellMouseGetInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void ps3_input_poll(void *data)
{
   ps3_input_t *ps3 = (ps3_input_t*)data;

   if (ps3 && ps3->joypad)
      ps3->joypad->poll();

#ifdef HAVE_MOUSE
   CellMouseInfo mouse_info;
   cellMouseGetInfo(&mouse_info);
   ps3->mice_connected = mouse_info.now_connect;
#endif
}