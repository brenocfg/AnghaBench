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
struct TYPE_5__ {TYPE_1__* g; } ;
struct TYPE_4__ {int /*<<< orphan*/  format_opts; int /*<<< orphan*/  codec_opts; } ;
typedef  TYPE_2__ OptionsContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * codec_opts ; 
 int /*<<< orphan*/ * format_opts ; 
 int opt_default (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static int opt_default_new(OptionsContext *o, const char *opt, const char *arg)
{
    int ret;
    AVDictionary *cbak = codec_opts;
    AVDictionary *fbak = format_opts;
    codec_opts = NULL;
    format_opts = NULL;

    ret = opt_default(NULL, opt, arg);

    av_dict_copy(&o->g->codec_opts , codec_opts, 0);
    av_dict_copy(&o->g->format_opts, format_opts, 0);
    av_dict_free(&codec_opts);
    av_dict_free(&format_opts);
    codec_opts = cbak;
    format_opts = fbak;

    return ret;
}