#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ codec_id; scalar_t__ extradata_size; int /*<<< orphan*/  extradata; } ;
struct TYPE_12__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {TYPE_1__** streams; } ;
struct TYPE_10__ {size_t* streams; int nb_streams; } ;
struct TYPE_9__ {TYPE_5__* codecpar; int /*<<< orphan*/  metadata; } ;
typedef  TYPE_2__ AdaptationSet ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVDictionaryEntry ;
typedef  TYPE_5__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  TRACK_NUMBER ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bitstream_switching(AVFormatContext *s, AdaptationSet *as) {
    int i;
    AVDictionaryEntry *gold_track_num = av_dict_get(s->streams[as->streams[0]]->metadata,
                                                    TRACK_NUMBER, NULL, 0);
    AVCodecParameters *gold_par = s->streams[as->streams[0]]->codecpar;
    if (!gold_track_num) return 0;
    for (i = 1; i < as->nb_streams; i++) {
        AVDictionaryEntry *track_num = av_dict_get(s->streams[as->streams[i]]->metadata,
                                                   TRACK_NUMBER, NULL, 0);
        AVCodecParameters *par = s->streams[as->streams[i]]->codecpar;
        if (!track_num ||
            strncmp(gold_track_num->value, track_num->value, strlen(gold_track_num->value)) ||
            gold_par->codec_id != par->codec_id ||
            gold_par->extradata_size != par->extradata_size ||
            memcmp(gold_par->extradata, par->extradata, par->extradata_size)) {
            return 0;
        }
    }
    return 1;
}