#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ request_probe; TYPE_2__* internal; TYPE_1__* codecpar; } ;
struct TYPE_9__ {scalar_t__ stream_type; scalar_t__ codec_type; scalar_t__ codec_id; } ;
struct TYPE_8__ {int need_context_update; } ;
struct TYPE_7__ {scalar_t__ codec_type; scalar_t__ codec_id; } ;
typedef  TYPE_3__ StreamType ;
typedef  TYPE_4__ AVStream ;

/* Variables and functions */

__attribute__((used)) static void mpegts_find_stream_type(AVStream *st,
                                    uint32_t stream_type,
                                    const StreamType *types)
{
    for (; types->stream_type; types++)
        if (stream_type == types->stream_type) {
            if (st->codecpar->codec_type != types->codec_type ||
                st->codecpar->codec_id   != types->codec_id) {
                st->codecpar->codec_type = types->codec_type;
                st->codecpar->codec_id   = types->codec_id;
                st->internal->need_context_update = 1;
            }
            st->request_probe        = 0;
            return;
        }
}