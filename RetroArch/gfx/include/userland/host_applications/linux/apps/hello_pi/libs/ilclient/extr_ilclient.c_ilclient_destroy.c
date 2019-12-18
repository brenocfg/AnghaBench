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
struct TYPE_4__ {int /*<<< orphan*/  event_sema; } ;
typedef  TYPE_1__ ILCLIENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_log_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

void ilclient_destroy(ILCLIENT_T *st)
{
   vcos_semaphore_delete(&st->event_sema);
   vcos_free(st);
   vcos_log_unregister(VCOS_LOG_CATEGORY);
}