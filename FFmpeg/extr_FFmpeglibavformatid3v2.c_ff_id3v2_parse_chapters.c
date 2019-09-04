#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  metadata; } ;
struct TYPE_13__ {int member_0; int member_1; } ;
struct TYPE_12__ {TYPE_1__* data; int /*<<< orphan*/  tag; struct TYPE_12__* next; } ;
struct TYPE_11__ {int /*<<< orphan*/  meta; int /*<<< orphan*/  element_id; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ ID3v2ExtraMetaCHAP ;
typedef  TYPE_2__ ID3v2ExtraMeta ;
typedef  TYPE_3__ AVRational ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_4__ AVChapter ;

/* Variables and functions */
 int av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_dynarray_add_nofree (TYPE_1__***,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__***) ; 
 TYPE_4__* avpriv_new_chapter (int /*<<< orphan*/ *,int,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int ff_id3v2_parse_chapters(AVFormatContext *s, ID3v2ExtraMeta **extra_meta)
{
    int ret = 0;
    ID3v2ExtraMeta *cur;
    AVRational time_base = {1, 1000};
    ID3v2ExtraMetaCHAP **chapters = NULL;
    int num_chapters = 0;
    int i;

    // since extra_meta is a linked list where elements are prepended,
    // we need to reverse the order of chapters
    for (cur = *extra_meta; cur; cur = cur->next) {
        ID3v2ExtraMetaCHAP *chap;

        if (strcmp(cur->tag, "CHAP"))
            continue;
        chap = cur->data;

        if ((ret = av_dynarray_add_nofree(&chapters, &num_chapters, chap)) < 0)
            goto end;
    }

    for (i = 0; i < (num_chapters / 2); i++) {
        ID3v2ExtraMetaCHAP *right;
        int right_index;

        right_index = (num_chapters - 1) - i;
        right = chapters[right_index];

        chapters[right_index] = chapters[i];
        chapters[i] = right;
    }

    for (i = 0; i < num_chapters; i++) {
        ID3v2ExtraMetaCHAP *chap;
        AVChapter *chapter;

        chap = chapters[i];
        chapter = avpriv_new_chapter(s, i, time_base, chap->start, chap->end, chap->element_id);
        if (!chapter)
            continue;

        if ((ret = av_dict_copy(&chapter->metadata, chap->meta, 0)) < 0)
            goto end;
    }

end:
    av_freep(&chapters);
    return ret;
}