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
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; scalar_t__ owner; scalar_t__ count; } ;
typedef  TYPE_1__ VCOS_REENTRANT_MUTEX_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_mutex_create (int /*<<< orphan*/ *,char const*) ; 

VCOS_STATUS_T vcos_generic_reentrant_mutex_create(VCOS_REENTRANT_MUTEX_T *m, const char *name)
{
   m->count = 0;
   m->owner = 0;
   return vcos_mutex_create(&m->mutex, name);
}