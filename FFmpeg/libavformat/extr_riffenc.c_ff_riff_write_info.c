#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pb; int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_MATCH_CASE ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_end_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_metadata_conv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_riff_info_conv ; 
 int /*<<< orphan*/  ff_riff_write_info_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_start_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  riff_has_valid_tags (TYPE_1__*) ; 
 scalar_t__** riff_tags ; 

void ff_riff_write_info(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    int i;
    int64_t list_pos;
    AVDictionaryEntry *t = NULL;

    ff_metadata_conv(&s->metadata, ff_riff_info_conv, NULL);

    /* writing empty LIST is not nice and may cause problems */
    if (!riff_has_valid_tags(s))
        return;

    list_pos = ff_start_tag(pb, "LIST");
    ffio_wfourcc(pb, "INFO");
    for (i = 0; *riff_tags[i]; i++)
        if ((t = av_dict_get(s->metadata, riff_tags[i],
                             NULL, AV_DICT_MATCH_CASE)))
            ff_riff_write_info_tag(s->pb, t->key, t->value);
    ff_end_tag(pb, list_pos);
}