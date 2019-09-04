#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_18__ {int nb_items; TYPE_4__* item; int /*<<< orphan*/  allocated_size; } ;
struct TYPE_17__ {TYPE_7__ frag_index; TYPE_2__* fc; } ;
struct TYPE_16__ {scalar_t__ moof_offset; int nb_stream_info; TYPE_3__* stream_info; scalar_t__ current; scalar_t__ headers_read; } ;
struct TYPE_15__ {scalar_t__ id; int index_entry; int /*<<< orphan*/ * encryption_index; void* first_tfra_pts; void* tfdt_dts; void* sidx_pts; } ;
struct TYPE_14__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_13__ {scalar_t__ id; } ;
typedef  TYPE_3__ MOVFragmentStreamInfo ;
typedef  TYPE_4__ MOVFragmentIndexItem ;
typedef  TYPE_5__ MOVContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 void* AV_NOPTS_VALUE ; 
 TYPE_4__* av_fast_realloc (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* av_realloc_array (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memmove (TYPE_4__*,TYPE_4__*,int) ; 
 int search_frag_moof_offset (TYPE_7__*,scalar_t__) ; 

__attribute__((used)) static int update_frag_index(MOVContext *c, int64_t offset)
{
    int index, i;
    MOVFragmentIndexItem * item;
    MOVFragmentStreamInfo * frag_stream_info;

    // If moof_offset already exists in frag_index, return index to it
    index = search_frag_moof_offset(&c->frag_index, offset);
    if (index < c->frag_index.nb_items &&
        c->frag_index.item[index].moof_offset == offset)
        return index;

    // offset is not yet in frag index.
    // Insert new item at index (sorted by moof offset)
    item = av_fast_realloc(c->frag_index.item,
                           &c->frag_index.allocated_size,
                           (c->frag_index.nb_items + 1) *
                           sizeof(*c->frag_index.item));
    if(!item)
        return -1;
    c->frag_index.item = item;

    frag_stream_info = av_realloc_array(NULL, c->fc->nb_streams,
                                        sizeof(*item->stream_info));
    if (!frag_stream_info)
        return -1;

    for (i = 0; i < c->fc->nb_streams; i++) {
        // Avoid building frag index if streams lack track id.
        if (c->fc->streams[i]->id < 0)
            return AVERROR_INVALIDDATA;

        frag_stream_info[i].id = c->fc->streams[i]->id;
        frag_stream_info[i].sidx_pts = AV_NOPTS_VALUE;
        frag_stream_info[i].tfdt_dts = AV_NOPTS_VALUE;
        frag_stream_info[i].first_tfra_pts = AV_NOPTS_VALUE;
        frag_stream_info[i].index_entry = -1;
        frag_stream_info[i].encryption_index = NULL;
    }

    if (index < c->frag_index.nb_items)
        memmove(c->frag_index.item + index + 1, c->frag_index.item + index,
                (c->frag_index.nb_items - index) * sizeof(*c->frag_index.item));

    item = &c->frag_index.item[index];
    item->headers_read = 0;
    item->current = 0;
    item->nb_stream_info = c->fc->nb_streams;
    item->moof_offset = offset;
    item->stream_info = frag_stream_info;
    c->frag_index.nb_items++;

    return index;
}