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
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_5__ {scalar_t__ nb_allocated; scalar_t__ dpb_size; } ;
typedef  TYPE_1__ NVDECFramePool ;
typedef  TYPE_2__ AVBufferRef ;

/* Variables and functions */
 TYPE_2__* av_buffer_alloc (int) ; 

__attribute__((used)) static AVBufferRef *nvdec_decoder_frame_alloc(void *opaque, int size)
{
    NVDECFramePool *pool = opaque;
    AVBufferRef *ret;

    if (pool->nb_allocated >= pool->dpb_size)
        return NULL;

    ret = av_buffer_alloc(sizeof(unsigned int));
    if (!ret)
        return NULL;

    *(unsigned int*)ret->data = pool->nb_allocated++;

    return ret;
}