#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; TYPE_1__* iformat; int /*<<< orphan*/ * pb; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  (* read_close ) (TYPE_2__*) ;int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVFMT_FLAG_CUSTOM_IO ; 
 int AVFMT_NOFILE ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_2__*) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_packet_queue (TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void avformat_close_input(AVFormatContext **ps)
{
    AVFormatContext *s;
    AVIOContext *pb;

    if (!ps || !*ps)
        return;

    s  = *ps;
    pb = s->pb;

    if ((s->iformat && strcmp(s->iformat->name, "image2") && s->iformat->flags & AVFMT_NOFILE) ||
        (s->flags & AVFMT_FLAG_CUSTOM_IO))
        pb = NULL;

    flush_packet_queue(s);

    if (s->iformat)
        if (s->iformat->read_close)
            s->iformat->read_close(s);

    avformat_free_context(s);

    *ps = NULL;

    avio_close(pb);
}