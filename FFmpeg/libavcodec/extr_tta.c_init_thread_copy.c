#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {TYPE_2__* avctx; } ;
typedef  TYPE_1__ TTAContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int allocate_buffers (TYPE_2__*) ; 

__attribute__((used)) static int init_thread_copy(AVCodecContext *avctx)
{
    TTAContext *s = avctx->priv_data;
    s->avctx = avctx;
    return allocate_buffers(avctx);
}