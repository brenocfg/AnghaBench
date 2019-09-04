#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_1__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  INT32_MIN ; 
 TYPE_1__* av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_replaygain_export_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ff_replaygain_export(AVStream *st, AVDictionary *metadata)
{
    const AVDictionaryEntry *tg, *tp, *ag, *ap;

    tg = av_dict_get(metadata, "REPLAYGAIN_TRACK_GAIN", NULL, 0);
    tp = av_dict_get(metadata, "REPLAYGAIN_TRACK_PEAK", NULL, 0);
    ag = av_dict_get(metadata, "REPLAYGAIN_ALBUM_GAIN", NULL, 0);
    ap = av_dict_get(metadata, "REPLAYGAIN_ALBUM_PEAK", NULL, 0);

    return ff_replaygain_export_raw(st,
                             parse_value(tg ? tg->value : NULL, INT32_MIN),
                             parse_value(tp ? tp->value : NULL, 0),
                             parse_value(ag ? ag->value : NULL, INT32_MIN),
                             parse_value(ap ? ap->value : NULL, 0));
}