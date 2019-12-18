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
typedef  int /*<<< orphan*/  VCOS_MSGQUEUE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_msgq_delete_internal (int /*<<< orphan*/ *) ; 

void vcos_msgq_delete(VCOS_MSGQUEUE_T *q)
{
   vcos_msgq_delete_internal(q);
}