#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  attr ;
typedef  int /*<<< orphan*/  PayloadContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* av_malloc (int) ; 
 scalar_t__ ff_rtsp_next_attr_and_value (char const**,char*,int,char*,int) ; 
 int strlen (char const*) ; 

int ff_parse_fmtp(AVFormatContext *s,
                  AVStream *stream, PayloadContext *data, const char *p,
                  int (*parse_fmtp)(AVFormatContext *s,
                                    AVStream *stream,
                                    PayloadContext *data,
                                    const char *attr, const char *value))
{
    char attr[256];
    char *value;
    int res;
    int value_size = strlen(p) + 1;

    if (!(value = av_malloc(value_size))) {
        av_log(s, AV_LOG_ERROR, "Failed to allocate data for FMTP.\n");
        return AVERROR(ENOMEM);
    }

    // remove protocol identifier
    while (*p && *p == ' ')
        p++;                     // strip spaces
    while (*p && *p != ' ')
        p++;                     // eat protocol identifier
    while (*p && *p == ' ')
        p++;                     // strip trailing spaces

    while (ff_rtsp_next_attr_and_value(&p,
                                       attr, sizeof(attr),
                                       value, value_size)) {
        res = parse_fmtp(s, stream, data, attr, value);
        if (res < 0 && res != AVERROR_PATCHWELCOME) {
            av_free(value);
            return res;
        }
    }
    av_free(value);
    return 0;
}