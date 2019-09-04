#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int flags; TYPE_1__* priv_data; } ;
struct TYPE_5__ {char const* allowed_extensions; int /*<<< orphan*/  interrupt_callback; } ;
typedef  TYPE_1__ DASHContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVFMT_FLAG_CUSTOM_IO ; 
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_OPT_SEARCH_CHILDREN ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  av_match_ext (char const*,char const*) ; 
 int /*<<< orphan*/  av_opt_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int av_strstart (char const*,char*,int /*<<< orphan*/ *) ; 
 char* avio_find_protocol_name (char const*) ; 
 int avio_open2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int open_url(AVFormatContext *s, AVIOContext **pb, const char *url,
                    AVDictionary *opts, AVDictionary *opts2, int *is_http)
{
    DASHContext *c = s->priv_data;
    AVDictionary *tmp = NULL;
    const char *proto_name = NULL;
    int ret;

    av_dict_copy(&tmp, opts, 0);
    av_dict_copy(&tmp, opts2, 0);

    if (av_strstart(url, "crypto", NULL)) {
        if (url[6] == '+' || url[6] == ':')
            proto_name = avio_find_protocol_name(url + 7);
    }

    if (!proto_name)
        proto_name = avio_find_protocol_name(url);

    if (!proto_name)
        return AVERROR_INVALIDDATA;

    // only http(s) & file are allowed
    if (av_strstart(proto_name, "file", NULL)) {
        if (strcmp(c->allowed_extensions, "ALL") && !av_match_ext(url, c->allowed_extensions)) {
            av_log(s, AV_LOG_ERROR,
                   "Filename extension of \'%s\' is not a common multimedia extension, blocked for security reasons.\n"
                   "If you wish to override this adjust allowed_extensions, you can set it to \'ALL\' to allow all\n",
                   url);
            return AVERROR_INVALIDDATA;
        }
    } else if (av_strstart(proto_name, "http", NULL)) {
        ;
    } else
        return AVERROR_INVALIDDATA;

    if (!strncmp(proto_name, url, strlen(proto_name)) && url[strlen(proto_name)] == ':')
        ;
    else if (av_strstart(url, "crypto", NULL) && !strncmp(proto_name, url + 7, strlen(proto_name)) && url[7 + strlen(proto_name)] == ':')
        ;
    else if (strcmp(proto_name, "file") || !strncmp(url, "file,", 5))
        return AVERROR_INVALIDDATA;

    av_freep(pb);
    ret = avio_open2(pb, url, AVIO_FLAG_READ, c->interrupt_callback, &tmp);
    if (ret >= 0) {
        // update cookies on http response with setcookies.
        char *new_cookies = NULL;

        if (!(s->flags & AVFMT_FLAG_CUSTOM_IO))
            av_opt_get(*pb, "cookies", AV_OPT_SEARCH_CHILDREN, (uint8_t**)&new_cookies);

        if (new_cookies) {
            av_dict_set(&opts, "cookies", new_cookies, AV_DICT_DONT_STRDUP_VAL);
        }

    }

    av_dict_free(&tmp);

    if (is_http)
        *is_http = av_strstart(proto_name, "http", NULL);

    return ret;
}