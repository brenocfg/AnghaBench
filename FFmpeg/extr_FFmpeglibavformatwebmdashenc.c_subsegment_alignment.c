#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  value; } ;
struct TYPE_10__ {TYPE_1__** streams; } ;
struct TYPE_9__ {size_t* streams; int nb_streams; } ;
struct TYPE_8__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_2__ AdaptationSet ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  CUE_TIMESTAMPS ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int subsegment_alignment(AVFormatContext *s, AdaptationSet *as) {
    int i;
    AVDictionaryEntry *gold = av_dict_get(s->streams[as->streams[0]]->metadata,
                                          CUE_TIMESTAMPS, NULL, 0);
    if (!gold) return 0;
    for (i = 1; i < as->nb_streams; i++) {
        AVDictionaryEntry *ts = av_dict_get(s->streams[as->streams[i]]->metadata,
                                            CUE_TIMESTAMPS, NULL, 0);
        if (!ts || strncmp(gold->value, ts->value, strlen(gold->value))) return 0;
    }
    return 1;
}