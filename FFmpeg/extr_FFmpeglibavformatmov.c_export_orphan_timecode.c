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
struct TYPE_10__ {int nb_streams; int /*<<< orphan*/  metadata; TYPE_2__** streams; } ;
struct TYPE_9__ {int /*<<< orphan*/  metadata; TYPE_1__* codecpar; } ;
struct TYPE_8__ {scalar_t__ codec_tag; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVDictionaryEntry ;

/* Variables and functions */
 scalar_t__ MKTAG (char,char,char,char) ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmcd_is_referenced (TYPE_3__*,int) ; 

__attribute__((used)) static void export_orphan_timecode(AVFormatContext *s)
{
    int i;

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];

        if (st->codecpar->codec_tag  == MKTAG('t','m','c','d') &&
            !tmcd_is_referenced(s, i + 1)) {
            AVDictionaryEntry *tcr = av_dict_get(st->metadata, "timecode", NULL, 0);
            if (tcr) {
                av_dict_set(&s->metadata, "timecode", tcr->value, 0);
                break;
            }
        }
    }
}