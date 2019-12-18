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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  stop; } ;
typedef  TYPE_1__ SVP_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t svp_get_stop(SVP_T *svp)
{
   uint32_t stop;

   vcos_mutex_lock(&svp->mutex);
   stop = svp->stop;
   vcos_mutex_unlock(&svp->mutex);

   return stop;
}