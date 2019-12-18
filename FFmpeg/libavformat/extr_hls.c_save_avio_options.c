#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  avio_opts; } ;
typedef  TYPE_1__ HLSContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int AV_OPT_ALLOW_NULL ; 
 int AV_OPT_SEARCH_CHILDREN ; 
 int av_dict_set (int /*<<< orphan*/ *,char const* const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ av_opt_get (int /*<<< orphan*/ ,char const* const,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int save_avio_options(AVFormatContext *s)
{
    HLSContext *c = s->priv_data;
    static const char * const opts[] = {
        "headers", "http_proxy", "user_agent", "cookies", "referer", "rw_timeout", NULL };
    const char * const * opt = opts;
    uint8_t *buf;
    int ret = 0;

    while (*opt) {
        if (av_opt_get(s->pb, *opt, AV_OPT_SEARCH_CHILDREN | AV_OPT_ALLOW_NULL, &buf) >= 0) {
            ret = av_dict_set(&c->avio_opts, *opt, buf,
                              AV_DICT_DONT_STRDUP_VAL);
            if (ret < 0)
                return ret;
        }
        opt++;
    }

    return ret;
}