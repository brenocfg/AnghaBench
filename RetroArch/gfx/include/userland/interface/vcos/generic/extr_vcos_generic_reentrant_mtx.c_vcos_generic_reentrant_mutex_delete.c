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
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ VCOS_REENTRANT_MUTEX_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 

void vcos_generic_reentrant_mutex_delete(VCOS_REENTRANT_MUTEX_T *m)
{
   vcos_assert(m->count == 0);
   vcos_mutex_delete(&m->mutex);
}