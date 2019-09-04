#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* shortest_end; int /*<<< orphan*/  raw_packet_buffer_remaining_size; void* offset; } ;
struct TYPE_7__ {TYPE_5__* internal; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  RAW_PACKET_BUFFER_SIZE ; 
 TYPE_1__* av_malloc (int) ; 
 TYPE_5__* av_mallocz (int) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_1__*) ; 
 int /*<<< orphan*/  avformat_get_context_defaults (TYPE_1__*) ; 

AVFormatContext *avformat_alloc_context(void)
{
    AVFormatContext *ic;
    ic = av_malloc(sizeof(AVFormatContext));
    if (!ic) return ic;
    avformat_get_context_defaults(ic);

    ic->internal = av_mallocz(sizeof(*ic->internal));
    if (!ic->internal) {
        avformat_free_context(ic);
        return NULL;
    }
    ic->internal->offset = AV_NOPTS_VALUE;
    ic->internal->raw_packet_buffer_remaining_size = RAW_PACKET_BUFFER_SIZE;
    ic->internal->shortest_end = AV_NOPTS_VALUE;

    return ic;
}