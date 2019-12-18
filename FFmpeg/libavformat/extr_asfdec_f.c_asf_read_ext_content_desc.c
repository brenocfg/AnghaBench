#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {TYPE_1__* dar; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_6__ {void* den; void* num; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ ASFContext ;

/* Variables and functions */
 int avio_get_str16le (int /*<<< orphan*/ *,int,char*,int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_tag (TYPE_2__*,char*,int,int,int) ; 
 void* get_value (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int asf_read_ext_content_desc(AVFormatContext *s, int64_t size)
{
    AVIOContext *pb = s->pb;
    ASFContext *asf = s->priv_data;
    int desc_count, i, ret;

    desc_count = avio_rl16(pb);
    for (i = 0; i < desc_count; i++) {
        int name_len, value_type, value_len;
        char name[1024];

        name_len = avio_rl16(pb);
        if (name_len % 2)   // must be even, broken lavf versions wrote len-1
            name_len += 1;
        if ((ret = avio_get_str16le(pb, name_len, name, sizeof(name))) < name_len)
            avio_skip(pb, name_len - ret);
        value_type = avio_rl16(pb);
        value_len  = avio_rl16(pb);
        if (!value_type && value_len % 2)
            value_len += 1;
        /* My sample has that stream set to 0 maybe that mean the container.
         * ASF stream count starts at 1. I am using 0 to the container value
         * since it's unused. */
        if (!strcmp(name, "AspectRatioX"))
            asf->dar[0].num = get_value(s->pb, value_type, 32);
        else if (!strcmp(name, "AspectRatioY"))
            asf->dar[0].den = get_value(s->pb, value_type, 32);
        else
            get_tag(s, name, value_type, value_len, 32);
    }

    return 0;
}