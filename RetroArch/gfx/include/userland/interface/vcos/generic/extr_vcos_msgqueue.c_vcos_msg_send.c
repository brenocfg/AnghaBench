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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {scalar_t__ magic; } ;
typedef  TYPE_1__ VCOS_MSG_T ;
typedef  int /*<<< orphan*/  VCOS_MSGQUEUE_T ;

/* Variables and functions */
 scalar_t__ MAGIC ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_msg_send_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

void vcos_msg_send(VCOS_MSGQUEUE_T *dest, uint32_t code, VCOS_MSG_T *msg)
{
   vcos_assert(msg->magic == MAGIC);
   vcos_msg_send_helper(NULL, dest, code, msg);
}