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
typedef  int /*<<< orphan*/  PayloadContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int atoi (char const*) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ *,char*) ; 
 int parse_fmtp_config (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int parse_fmtp(AVFormatContext *s,
                      AVStream *stream, PayloadContext *data,
                      const char *attr, const char *value)
{
    int res;

    if (!strcmp(attr, "config")) {
        res = parse_fmtp_config(stream, value);
        if (res < 0)
            return res;
    } else if (!strcmp(attr, "cpresent")) {
        int cpresent = atoi(value);
        if (cpresent != 0)
            avpriv_request_sample(s,
                                  "RTP MP4A-LATM with in-band configuration");
    }

    return 0;
}