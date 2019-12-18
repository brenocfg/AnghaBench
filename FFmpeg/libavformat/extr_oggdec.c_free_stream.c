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
struct ogg_stream {int /*<<< orphan*/  new_metadata; int /*<<< orphan*/  private; TYPE_1__* codec; int /*<<< orphan*/  buf; } ;
struct ogg {struct ogg_stream* streams; } ;
struct TYPE_6__ {struct ogg* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cleanup ) (TYPE_2__*,int) ;} ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static void free_stream(AVFormatContext *s, int i)
{
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *stream = &ogg->streams[i];

    av_freep(&stream->buf);
    if (stream->codec &&
        stream->codec->cleanup) {
        stream->codec->cleanup(s, i);
    }

    av_freep(&stream->private);
    av_freep(&stream->new_metadata);
}