#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ebml_master ;
struct TYPE_11__ {int /*<<< orphan*/  key; } ;
struct TYPE_10__ {TYPE_1__* priv_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  tags_bc; } ;
typedef  TYPE_1__ MatroskaMuxContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 TYPE_3__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_ebml_master (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mkv_check_tag_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mkv_write_simpletag (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int mkv_write_tag_targets (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mkv_write_tag(AVFormatContext *s, AVDictionary *m, uint32_t elementid,
                         unsigned int uid)
{
    MatroskaMuxContext *mkv = s->priv_data;
    ebml_master tag;
    int ret;
    AVDictionaryEntry *t = NULL;

    ret = mkv_write_tag_targets(s, elementid, uid, &tag);
    if (ret < 0)
        return ret;

    while ((t = av_dict_get(m, "", t, AV_DICT_IGNORE_SUFFIX))) {
        if (mkv_check_tag_name(t->key, elementid)) {
            ret = mkv_write_simpletag(mkv->tags_bc, t);
            if (ret < 0)
                return ret;
        }
    }

    end_ebml_master(mkv->tags_bc, tag);
    return 0;
}