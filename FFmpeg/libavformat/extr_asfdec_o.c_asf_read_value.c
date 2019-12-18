#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int ASF_UNICODE ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_dict_set (int /*<<< orphan*/ **,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 char* av_malloc (int) ; 
 int avio_read (int /*<<< orphan*/ *,char*,int) ; 
 int get_asf_string (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int asf_read_value(AVFormatContext *s, const uint8_t *name,
                          uint16_t val_len, int type, AVDictionary **met)
{
    int ret;
    uint8_t *value;
    uint16_t buflen = 2 * val_len + 1;
    AVIOContext *pb = s->pb;

    value = av_malloc(buflen);
    if (!value)
        return AVERROR(ENOMEM);
    if (type == ASF_UNICODE) {
        // get_asf_string reads UTF-16 and converts it to UTF-8 which needs longer buffer
        if ((ret = get_asf_string(pb, val_len, value, buflen)) < 0)
            goto failed;
        if (av_dict_set(met, name, value, 0) < 0)
            av_log(s, AV_LOG_WARNING, "av_dict_set failed.\n");
    } else {
        char buf[256];
        if (val_len > sizeof(buf)) {
            ret = AVERROR_INVALIDDATA;
            goto failed;
        }
        if ((ret = avio_read(pb, value, val_len)) < 0)
            goto failed;
        if (ret < 2 * val_len)
            value[ret] = '\0';
        else
            value[2 * val_len - 1] = '\0';
        snprintf(buf, sizeof(buf), "%s", value);
        if (av_dict_set(met, name, buf, 0) < 0)
            av_log(s, AV_LOG_WARNING, "av_dict_set failed.\n");
    }
    av_freep(&value);

    return 0;

failed:
    av_freep(&value);
    return ret;
}