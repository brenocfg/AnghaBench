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
struct TYPE_9__ {TYPE_2__* oformat; TYPE_1__* internal; } ;
struct TYPE_8__ {scalar_t__ init; } ;
struct TYPE_7__ {int initialized; int streams_initialized; } ;
typedef  TYPE_3__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVSTREAM_INIT_IN_INIT_OUTPUT ; 
 int AVSTREAM_INIT_IN_WRITE_HEADER ; 
 int init_muxer (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int init_pts (TYPE_3__*) ; 

int avformat_init_output(AVFormatContext *s, AVDictionary **options)
{
    int ret = 0;

    if ((ret = init_muxer(s, options)) < 0)
        return ret;

    s->internal->initialized = 1;
    s->internal->streams_initialized = ret;

    if (s->oformat->init && ret) {
        if ((ret = init_pts(s)) < 0)
            return ret;

        return AVSTREAM_INIT_IN_INIT_OUTPUT;
    }

    return AVSTREAM_INIT_IN_WRITE_HEADER;
}