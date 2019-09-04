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
struct TYPE_3__ {int /*<<< orphan*/  async_mutex; int /*<<< orphan*/  async_cond; scalar_t__ async_lock; } ;
typedef  TYPE_1__ FrameThreadContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (scalar_t__) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void async_unlock(FrameThreadContext *fctx)
{
    pthread_mutex_lock(&fctx->async_mutex);
    av_assert0(fctx->async_lock);
    fctx->async_lock = 0;
    pthread_cond_broadcast(&fctx->async_cond);
    pthread_mutex_unlock(&fctx->async_mutex);
}