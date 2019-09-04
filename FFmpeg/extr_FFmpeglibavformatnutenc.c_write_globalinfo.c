#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct TYPE_9__ {int /*<<< orphan*/  metadata; } ;
struct TYPE_8__ {TYPE_2__* avf; } ;
typedef  TYPE_1__ NUTContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 scalar_t__ add_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_put_v (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_standardize_creation_time (TYPE_2__*) ; 

__attribute__((used)) static int write_globalinfo(NUTContext *nut, AVIOContext *bc)
{
    AVFormatContext *s   = nut->avf;
    AVDictionaryEntry *t = NULL;
    AVIOContext *dyn_bc;
    uint8_t *dyn_buf = NULL;
    int count        = 0, dyn_size;
    int ret          = avio_open_dyn_buf(&dyn_bc);
    if (ret < 0)
        return ret;

    ff_standardize_creation_time(s);
    while ((t = av_dict_get(s->metadata, "", t, AV_DICT_IGNORE_SUFFIX)))
        count += add_info(dyn_bc, t->key, t->value);

    ff_put_v(bc, 0); //stream_if_plus1
    ff_put_v(bc, 0); //chapter_id
    ff_put_v(bc, 0); //timestamp_start
    ff_put_v(bc, 0); //length

    ff_put_v(bc, count);

    dyn_size = avio_close_dyn_buf(dyn_bc, &dyn_buf);
    avio_write(bc, dyn_buf, dyn_size);
    av_free(dyn_buf);
    return 0;
}