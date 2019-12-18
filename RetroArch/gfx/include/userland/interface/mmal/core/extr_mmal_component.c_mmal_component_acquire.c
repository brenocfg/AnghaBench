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
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {TYPE_1__* priv; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  refcount; } ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;
typedef  TYPE_3__ MMAL_COMPONENT_CORE_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

void mmal_component_acquire(MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_CORE_PRIVATE_T *private = (MMAL_COMPONENT_CORE_PRIVATE_T *)component->priv;

   LOG_TRACE("component %s(%d), refcount %i", component->name, component->id,
             component->priv->refcount);

   vcos_mutex_lock(&private->lock);
   component->priv->refcount++;
   vcos_mutex_unlock(&private->lock);
}