#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  value; } ;
struct TYPE_12__ {int /*<<< orphan*/  metadata; TYPE_1__* priv_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  metadata; } ;
struct TYPE_10__ {int /*<<< orphan*/  tc; } ;
typedef  TYPE_1__ MXFContext ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVDictionaryEntry ;

/* Variables and functions */
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int av_timecode_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int av_timecode_init_from_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int mxf_init_timecode(AVFormatContext *s, AVStream *st, AVRational rate)
{
    MXFContext *mxf = s->priv_data;
    AVDictionaryEntry *tcr = av_dict_get(s->metadata, "timecode", NULL, 0);
    if (!tcr)
        tcr = av_dict_get(st->metadata, "timecode", NULL, 0);

    if (tcr)
        return av_timecode_init_from_string(&mxf->tc, rate, tcr->value, s);
    else
        return av_timecode_init(&mxf->tc, rate, 0, 0, s);
}