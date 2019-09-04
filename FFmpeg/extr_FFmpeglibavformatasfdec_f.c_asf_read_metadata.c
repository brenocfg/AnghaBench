#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {TYPE_1__* dar; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_7__ {int num; int den; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ ASFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int avio_get_str16le (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_tag (TYPE_2__*,int /*<<< orphan*/ *,int,int,int) ; 
 int get_value (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int asf_read_metadata(AVFormatContext *s, int64_t size)
{
    AVIOContext *pb = s->pb;
    ASFContext *asf = s->priv_data;
    int n, stream_num, name_len_utf16, name_len_utf8, value_len;
    int ret, i;
    n = avio_rl16(pb);

    for (i = 0; i < n; i++) {
        uint8_t *name;
        int value_type;

        avio_rl16(pb);  // lang_list_index
        stream_num = avio_rl16(pb);
        name_len_utf16 = avio_rl16(pb);
        value_type = avio_rl16(pb); /* value_type */
        value_len  = avio_rl32(pb);

        name_len_utf8 = 2*name_len_utf16 + 1;
        name          = av_malloc(name_len_utf8);
        if (!name)
            return AVERROR(ENOMEM);

        if ((ret = avio_get_str16le(pb, name_len_utf16, name, name_len_utf8)) < name_len_utf16)
            avio_skip(pb, name_len_utf16 - ret);
        av_log(s, AV_LOG_TRACE, "%d stream %d name_len %2d type %d len %4d <%s>\n",
                i, stream_num, name_len_utf16, value_type, value_len, name);

        if (!strcmp(name, "AspectRatioX")){
            int aspect_x = get_value(s->pb, value_type, 16);
            if(stream_num < 128)
                asf->dar[stream_num].num = aspect_x;
        } else if(!strcmp(name, "AspectRatioY")){
            int aspect_y = get_value(s->pb, value_type, 16);
            if(stream_num < 128)
                asf->dar[stream_num].den = aspect_y;
        } else {
            get_tag(s, name, value_type, value_len, 16);
        }
        av_freep(&name);
    }

    return 0;
}