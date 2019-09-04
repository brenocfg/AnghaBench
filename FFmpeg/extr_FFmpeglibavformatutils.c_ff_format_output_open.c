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
struct TYPE_6__ {int (* io_open ) (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;int /*<<< orphan*/  pb; TYPE_1__* oformat; } ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_2__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVFMT_NOFILE ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  EINVAL ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int ff_format_output_open(AVFormatContext *s, const char *url, AVDictionary **options)
{
    if (!s->oformat)
        return AVERROR(EINVAL);

    if (!(s->oformat->flags & AVFMT_NOFILE))
        return s->io_open(s, &s->pb, url, AVIO_FLAG_WRITE, options);
    return 0;
}