#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_streams; TYPE_2__* priv_data; } ;
struct TYPE_8__ {TYPE_1__* streams; } ;
struct TYPE_7__ {scalar_t__ segment_type; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ OutputStream ;
typedef  TYPE_2__ DASHContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ SEGMENT_TYPE_WEBM ; 
 int avformat_write_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int flush_init_segment (TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static int dash_write_header(AVFormatContext *s)
{
    DASHContext *c = s->priv_data;
    int i, ret;
    for (i = 0; i < s->nb_streams; i++) {
        OutputStream *os = &c->streams[i];
        if ((ret = avformat_write_header(os->ctx, NULL)) < 0)
            return ret;

        // Flush init segment
        // Only for WebM segment, since for mp4 delay_moov is set and
        // the init segment is thus flushed after the first packets.
        if (os->segment_type == SEGMENT_TYPE_WEBM &&
            (ret = flush_init_segment(s, os)) < 0)
            return ret;
    }
    return ret;
}