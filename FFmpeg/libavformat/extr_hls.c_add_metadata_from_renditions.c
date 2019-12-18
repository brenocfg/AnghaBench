#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rendition {int type; int /*<<< orphan*/  disposition; scalar_t__* name; scalar_t__* language; } ;
struct playlist {int n_main_streams; int n_renditions; struct rendition** renditions; TYPE_2__** main_streams; } ;
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_4__ {int /*<<< orphan*/  disposition; int /*<<< orphan*/  metadata; TYPE_1__* codecpar; } ;
struct TYPE_3__ {int codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_metadata_from_renditions(AVFormatContext *s, struct playlist *pls,
                                         enum AVMediaType type)
{
    int rend_idx = 0;
    int i;

    for (i = 0; i < pls->n_main_streams; i++) {
        AVStream *st = pls->main_streams[i];

        if (st->codecpar->codec_type != type)
            continue;

        for (; rend_idx < pls->n_renditions; rend_idx++) {
            struct rendition *rend = pls->renditions[rend_idx];

            if (rend->type != type)
                continue;

            if (rend->language[0])
                av_dict_set(&st->metadata, "language", rend->language, 0);
            if (rend->name[0])
                av_dict_set(&st->metadata, "comment", rend->name, 0);

            st->disposition |= rend->disposition;
        }
        if (rend_idx >=pls->n_renditions)
            break;
    }
}