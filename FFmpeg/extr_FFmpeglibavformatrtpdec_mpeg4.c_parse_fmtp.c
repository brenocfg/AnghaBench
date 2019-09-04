#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; int offset; scalar_t__ str; } ;
struct TYPE_7__ {scalar_t__ codec_id; } ;
struct TYPE_6__ {TYPE_2__* codecpar; } ;
typedef  int /*<<< orphan*/  PayloadContext ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */
 scalar_t__ ATTR_NAME_TYPE_INT ; 
 scalar_t__ ATTR_NAME_TYPE_STR ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_AAC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int atoi (char const*) ; 
 TYPE_5__* attr_names ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  av_strcasecmp (char const*,scalar_t__) ; 
 char* av_strdup (char const*) ; 
 int parse_fmtp_config (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int parse_fmtp(AVFormatContext *s,
                      AVStream *stream, PayloadContext *data,
                      const char *attr, const char *value)
{
    AVCodecParameters *par = stream->codecpar;
    int res, i;

    if (!strcmp(attr, "config")) {
        res = parse_fmtp_config(par, value);

        if (res < 0)
            return res;
    }

    if (par->codec_id == AV_CODEC_ID_AAC) {
        /* Looking for a known attribute */
        for (i = 0; attr_names[i].str; ++i) {
            if (!av_strcasecmp(attr, attr_names[i].str)) {
                if (attr_names[i].type == ATTR_NAME_TYPE_INT) {
                    int val = atoi(value);
                    if (val > 32) {
                        av_log(s, AV_LOG_ERROR,
                               "The %s field size is invalid (%d)\n",
                               attr, val);
                        return AVERROR_INVALIDDATA;
                    }
                    *(int *)((char *)data+
                        attr_names[i].offset) = val;
                } else if (attr_names[i].type == ATTR_NAME_TYPE_STR) {
                    char *val = av_strdup(value);
                    if (!val)
                        return AVERROR(ENOMEM);
                    *(char **)((char *)data+
                        attr_names[i].offset) = val;
                }
            }
        }
    }
    return 0;
}