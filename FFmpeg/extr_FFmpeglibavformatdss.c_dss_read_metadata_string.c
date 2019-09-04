#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_dict_set (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_mallocz (unsigned int) ; 
 int avio_read (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dss_read_metadata_string(AVFormatContext *s, unsigned int offset,
                                    unsigned int size, const char *key)
{
    AVIOContext *pb = s->pb;
    char *value;
    int ret;

    avio_seek(pb, offset, SEEK_SET);

    value = av_mallocz(size + 1);
    if (!value)
        return AVERROR(ENOMEM);

    ret = avio_read(s->pb, value, size);
    if (ret < size) {
        ret = ret < 0 ? ret : AVERROR_EOF;
        goto exit;
    }

    ret = av_dict_set(&s->metadata, key, value, 0);

exit:
    av_free(value);
    return ret;
}