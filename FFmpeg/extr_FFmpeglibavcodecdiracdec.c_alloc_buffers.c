#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int width; int height; } ;
struct TYPE_5__ {int buffer_stride; void* mcscratch; void* mctmp; void* edge_emu_buffer_base; int /*<<< orphan*/  edge_emu_buffer; TYPE_1__ seq; } ;
typedef  TYPE_2__ DiracContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAX_BLOCKSIZE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_freep (void**) ; 
 void* av_malloc_array (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alloc_buffers(DiracContext *s, int stride)
{
    int w = s->seq.width;
    int h = s->seq.height;

    av_assert0(stride >= w);
    stride += 64;

    if (s->buffer_stride >= stride)
        return 0;
    s->buffer_stride = 0;

    av_freep(&s->edge_emu_buffer_base);
    memset(s->edge_emu_buffer, 0, sizeof(s->edge_emu_buffer));
    av_freep(&s->mctmp);
    av_freep(&s->mcscratch);

    s->edge_emu_buffer_base = av_malloc_array(stride, MAX_BLOCKSIZE);

    s->mctmp     = av_malloc_array((stride+MAX_BLOCKSIZE), (h+MAX_BLOCKSIZE) * sizeof(*s->mctmp));
    s->mcscratch = av_malloc_array(stride, MAX_BLOCKSIZE);

    if (!s->edge_emu_buffer_base || !s->mctmp || !s->mcscratch)
        return AVERROR(ENOMEM);

    s->buffer_stride = stride;
    return 0;
}