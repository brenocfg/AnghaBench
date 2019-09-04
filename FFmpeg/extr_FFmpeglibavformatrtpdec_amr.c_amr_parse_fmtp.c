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
struct TYPE_3__ {void* channels; void* interleaving; void* crc; void* octet_align; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 void* atoi (char const*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int amr_parse_fmtp(AVFormatContext *s,
                          AVStream *stream, PayloadContext *data,
                          const char *attr, const char *value)
{
    /* Some AMR SDP configurations contain "octet-align", without
     * the trailing =1. Therefore, if the value is empty,
     * interpret it as "1".
     */
    if (!strcmp(value, "")) {
        av_log(s, AV_LOG_WARNING, "AMR fmtp attribute %s had "
                                  "nonstandard empty value\n", attr);
        value = "1";
    }
    if (!strcmp(attr, "octet-align"))
        data->octet_align = atoi(value);
    else if (!strcmp(attr, "crc"))
        data->crc = atoi(value);
    else if (!strcmp(attr, "interleaving"))
        data->interleaving = atoi(value);
    else if (!strcmp(attr, "channels"))
        data->channels = atoi(value);
    return 0;
}