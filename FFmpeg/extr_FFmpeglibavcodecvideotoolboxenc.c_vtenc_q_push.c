#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__* q_tail; TYPE_2__* q_head; int /*<<< orphan*/  cv_sample_sent; } ;
typedef  TYPE_1__ VTEncContext ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/ * sei; int /*<<< orphan*/  cm_buffer; } ;
typedef  int /*<<< orphan*/  ExtraSEI ;
typedef  int /*<<< orphan*/  CMSampleBufferRef ;
typedef  TYPE_2__ BufNode ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRetain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* av_malloc (int) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_async_error (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vtenc_q_push(VTEncContext *vtctx, CMSampleBufferRef buffer, ExtraSEI *sei)
{
    BufNode *info = av_malloc(sizeof(BufNode));
    if (!info) {
        set_async_error(vtctx, AVERROR(ENOMEM));
        return;
    }

    CFRetain(buffer);
    info->cm_buffer = buffer;
    info->sei = sei;
    info->next = NULL;

    pthread_mutex_lock(&vtctx->lock);
    pthread_cond_signal(&vtctx->cv_sample_sent);

    if (!vtctx->q_head) {
        vtctx->q_head = info;
    } else {
        vtctx->q_tail->next = info;
    }

    vtctx->q_tail = info;

    pthread_mutex_unlock(&vtctx->lock);
}