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
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  stats; } ;
typedef  TYPE_1__ SVP_T ;
typedef  int /*<<< orphan*/  SVP_STATS_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

void svp_get_stats(SVP_T *svp, SVP_STATS_T *stats)
{
   vcos_mutex_lock(&svp->mutex);
   *stats = svp->stats;
   vcos_mutex_unlock(&svp->mutex);
}