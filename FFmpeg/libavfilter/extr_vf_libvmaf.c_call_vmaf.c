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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  vmaf_score; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ LIBVMAFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_vmaf_score (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *call_vmaf(void *ctx)
{
    LIBVMAFContext *s = (LIBVMAFContext *) ctx;
    compute_vmaf_score(s);
    if (!s->error) {
        av_log(ctx, AV_LOG_INFO, "VMAF score: %f\n",s->vmaf_score);
    } else {
        pthread_mutex_lock(&s->lock);
        pthread_cond_signal(&s->cond);
        pthread_mutex_unlock(&s->lock);
    }
    pthread_exit(NULL);
    return NULL;
}