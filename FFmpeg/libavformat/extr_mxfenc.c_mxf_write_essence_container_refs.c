#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  container_ul; } ;
struct TYPE_11__ {int nb_streams; TYPE_1__** streams; int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_10__ {int essence_container_count; } ;
struct TYPE_9__ {scalar_t__* track_essence_element_key; size_t index; } ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
typedef  TYPE_2__ MXFStreamContext ;
typedef  TYPE_3__ MXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  DESCRIPTOR_COUNT (int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  multiple_desc_ul ; 
 TYPE_6__* mxf_essence_container_uls ; 
 int /*<<< orphan*/  mxf_write_refs_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxf_write_essence_container_refs(AVFormatContext *s)
{
    MXFContext *c = s->priv_data;
    AVIOContext *pb = s->pb;
    int i;

    mxf_write_refs_count(pb, DESCRIPTOR_COUNT(c->essence_container_count));
    av_log(s,AV_LOG_DEBUG, "essence container count:%d\n", c->essence_container_count);
    for (i = 0; i < s->nb_streams; i++) {
        MXFStreamContext *sc = s->streams[i]->priv_data;
        // check first track of essence container type and only write it once
        if (sc->track_essence_element_key[15] != 0)
            continue;
        avio_write(pb, mxf_essence_container_uls[sc->index].container_ul, 16);
        if (c->essence_container_count == 1)
            break;
    }

    if (c->essence_container_count > 1)
        avio_write(pb, multiple_desc_ul, 16);
}