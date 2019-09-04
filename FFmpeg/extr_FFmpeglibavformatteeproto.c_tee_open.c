#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  is_streamed; int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_11__ {int child_count; TYPE_5__* child; } ;
typedef  TYPE_2__ TeeContext ;
struct TYPE_13__ {int /*<<< orphan*/  is_streamed; } ;
struct TYPE_12__ {TYPE_6__* url_context; } ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_FLAG_READ ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_get_token (char const**,int /*<<< orphan*/ ) ; 
 void* av_realloc_array (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  av_strstart (char const*,char*,char const**) ; 
 int /*<<< orphan*/  child_delim ; 
 int ff_tee_parse_slave_options (TYPE_1__*,char*,int /*<<< orphan*/ **,char**) ; 
 int ffurl_open_whitelist (TYPE_6__**,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strspn (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tee_close (TYPE_1__*) ; 

__attribute__((used)) static int tee_open(URLContext *h, const char *filename, int flags)
{
    TeeContext *c = h->priv_data;
    int ret, i;

    av_strstart(filename, "tee:", &filename);

    if (flags & AVIO_FLAG_READ)
        return AVERROR(ENOSYS);

    while (*filename) {
        char *child_string = av_get_token(&filename, child_delim);
        char *child_name = NULL;
        void *tmp;
        AVDictionary *options = NULL;
        if (!child_string) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        tmp = av_realloc_array(c->child, c->child_count + 1, sizeof(*c->child));
        if (!tmp) {
            ret = AVERROR(ENOMEM);
            goto loop_fail;
        }
        c->child = tmp;
        memset(&c->child[c->child_count], 0, sizeof(c->child[c->child_count]));

        ret = ff_tee_parse_slave_options(h, child_string, &options, &child_name);
        if (ret < 0)
            goto loop_fail;

        ret = ffurl_open_whitelist(&c->child[c->child_count].url_context, child_name, flags,
                                   &h->interrupt_callback, &options,
                                   h->protocol_whitelist, h->protocol_blacklist,
                                   h);
loop_fail:
        av_freep(&child_string);
        av_dict_free(&options);
        if (ret < 0)
            goto fail;
        c->child_count++;

        if (strspn(filename, child_delim))
            filename++;
    }

    h->is_streamed = 0;
    for (i=0; i<c->child_count; i++) {
        h->is_streamed |= c->child[i].url_context->is_streamed;
    }

    return 0;
fail:
    tee_close(h);
    return ret;
}