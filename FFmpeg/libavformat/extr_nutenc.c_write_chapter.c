#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {int start; int end; int /*<<< orphan*/  metadata; } ;
struct TYPE_13__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct TYPE_12__ {TYPE_2__* chapter; TYPE_1__* avf; } ;
struct TYPE_11__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_10__ {TYPE_5__** chapters; } ;
typedef  TYPE_3__ NUTContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVDictionaryEntry ;
typedef  TYPE_5__ AVChapter ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 scalar_t__ add_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_put_v (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_s (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_tt (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int write_chapter(NUTContext *nut, AVIOContext *bc, int id)
{
    AVIOContext *dyn_bc;
    uint8_t *dyn_buf     = NULL;
    AVDictionaryEntry *t = NULL;
    AVChapter *ch        = nut->avf->chapters[id];
    int ret, dyn_size, count = 0;

    ret = avio_open_dyn_buf(&dyn_bc);
    if (ret < 0)
        return ret;

    ff_put_v(bc, 0);                                        // stream_id_plus1
    put_s(bc, id + 1);                                      // chapter_id
    put_tt(nut, nut->chapter[id].time_base, bc, ch->start); // chapter_start
    ff_put_v(bc, ch->end - ch->start);                      // chapter_len

    while ((t = av_dict_get(ch->metadata, "", t, AV_DICT_IGNORE_SUFFIX)))
        count += add_info(dyn_bc, t->key, t->value);

    ff_put_v(bc, count);

    dyn_size = avio_close_dyn_buf(dyn_bc, &dyn_buf);
    avio_write(bc, dyn_buf, dyn_size);
    av_freep(&dyn_buf);
    return 0;
}