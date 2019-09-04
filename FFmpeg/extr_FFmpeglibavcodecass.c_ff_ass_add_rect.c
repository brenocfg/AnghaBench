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
struct TYPE_8__ {int num_rects; TYPE_1__** rects; } ;
struct TYPE_7__ {char* ass; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ AVSubtitleRect ;
typedef  TYPE_2__ AVSubtitle ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SUBTITLE_ASS ; 
 TYPE_1__* av_mallocz (int) ; 
 TYPE_1__** av_realloc_array (TYPE_1__**,int,int) ; 
 char* ff_ass_get_dialog (int,int,char const*,char const*,char const*) ; 

int ff_ass_add_rect(AVSubtitle *sub, const char *dialog,
                    int readorder, int layer, const char *style,
                    const char *speaker)
{
    char *ass_str;
    AVSubtitleRect **rects;

    rects = av_realloc_array(sub->rects, (sub->num_rects+1), sizeof(*sub->rects));
    if (!rects)
        return AVERROR(ENOMEM);
    sub->rects = rects;
    rects[sub->num_rects]       = av_mallocz(sizeof(*rects[0]));
    if (!rects[sub->num_rects])
        return AVERROR(ENOMEM);
    rects[sub->num_rects]->type = SUBTITLE_ASS;
    ass_str = ff_ass_get_dialog(readorder, layer, style, speaker, dialog);
    if (!ass_str)
        return AVERROR(ENOMEM);
    rects[sub->num_rects]->ass = ass_str;
    sub->num_rects++;
    return 0;
}