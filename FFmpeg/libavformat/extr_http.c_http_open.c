#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int is_streamed; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_8__ {int seekable; char* headers; int /*<<< orphan*/  chained_options; scalar_t__ listen; int /*<<< orphan*/  location; int /*<<< orphan*/  filesize; } ;
typedef  TYPE_2__ HTTPContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int av_reallocp (char**,int) ; 
 int /*<<< orphan*/  av_strdup (char const*) ; 
 int http_listen (TYPE_1__*,char const*,int,int /*<<< orphan*/ **) ; 
 int http_open_cnx (TYPE_1__*,int /*<<< orphan*/ **) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int http_open(URLContext *h, const char *uri, int flags,
                     AVDictionary **options)
{
    HTTPContext *s = h->priv_data;
    int ret;

    if( s->seekable == 1 )
        h->is_streamed = 0;
    else
        h->is_streamed = 1;

    s->filesize = UINT64_MAX;
    s->location = av_strdup(uri);
    if (!s->location)
        return AVERROR(ENOMEM);
    if (options)
        av_dict_copy(&s->chained_options, *options, 0);

    if (s->headers) {
        int len = strlen(s->headers);
        if (len < 2 || strcmp("\r\n", s->headers + len - 2)) {
            av_log(h, AV_LOG_WARNING,
                   "No trailing CRLF found in HTTP header. Adding it.\n");
            ret = av_reallocp(&s->headers, len + 3);
            if (ret < 0)
                return ret;
            s->headers[len]     = '\r';
            s->headers[len + 1] = '\n';
            s->headers[len + 2] = '\0';
        }
    }

    if (s->listen) {
        return http_listen(h, uri, flags, options);
    }
    ret = http_open_cnx(h, options);
    if (ret < 0)
        av_dict_free(&s->chained_options);
    return ret;
}