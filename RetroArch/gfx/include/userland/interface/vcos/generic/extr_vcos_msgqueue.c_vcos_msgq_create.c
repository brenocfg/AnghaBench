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
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
typedef  int /*<<< orphan*/  VCOS_MSGQUEUE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_msgq_create_internal (int /*<<< orphan*/ *,char const*) ; 

VCOS_STATUS_T vcos_msgq_create(VCOS_MSGQUEUE_T *q, const char *name)
{
   VCOS_STATUS_T st;

   st = vcos_msgq_create_internal(q, name);

   return st;
}