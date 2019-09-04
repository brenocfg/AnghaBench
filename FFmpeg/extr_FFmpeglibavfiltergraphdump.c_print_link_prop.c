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
typedef  int /*<<< orphan*/  layout ;
struct TYPE_9__ {int len; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_8__ {int type; scalar_t__ sample_rate; int /*<<< orphan*/  format; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; TYPE_1__ sample_aspect_ratio; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVBPrint ;

/* Variables and functions */
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  av_bprintf (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  av_get_channel_layout_string (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_get_sample_fmt_name (int /*<<< orphan*/ ) ; 
 char* av_x_if_null (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int print_link_prop(AVBPrint *buf, AVFilterLink *link)
{
    char *format;
    char layout[64];
    AVBPrint dummy_buffer = { 0 };

    if (!buf)
        buf = &dummy_buffer;
    switch (link->type) {
        case AVMEDIA_TYPE_VIDEO:
            format = av_x_if_null(av_get_pix_fmt_name(link->format), "?");
            av_bprintf(buf, "[%dx%d %d:%d %s]", link->w, link->h,
                    link->sample_aspect_ratio.num,
                    link->sample_aspect_ratio.den,
                    format);
            break;

        case AVMEDIA_TYPE_AUDIO:
            av_get_channel_layout_string(layout, sizeof(layout),
                                         link->channels, link->channel_layout);
            format = av_x_if_null(av_get_sample_fmt_name(link->format), "?");
            av_bprintf(buf, "[%dHz %s:%s]",
                       (int)link->sample_rate, format, layout);
            break;

        default:
            av_bprintf(buf, "?");
            break;
    }
    return buf->len;
}