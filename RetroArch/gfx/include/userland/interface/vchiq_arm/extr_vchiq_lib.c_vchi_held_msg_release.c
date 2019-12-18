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
typedef  int int32_t ;
struct TYPE_3__ {scalar_t__ message; int /*<<< orphan*/  service; } ;
typedef  TYPE_1__ VCHI_HELD_MSG_T ;

/* Variables and functions */
 int /*<<< orphan*/  free_msgbuf (scalar_t__) ; 

int32_t
vchi_held_msg_release( VCHI_HELD_MSG_T *message )
{
   int ret = -1;

   if (message && message->message && !message->service)
   {
      free_msgbuf(message->message);
      ret = 0;
   }

   return ret;
}