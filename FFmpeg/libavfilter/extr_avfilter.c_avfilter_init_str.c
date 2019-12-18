#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char const* key; } ;
struct TYPE_10__ {TYPE_1__* filter; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; int /*<<< orphan*/  priv_class; } ;
typedef  TYPE_2__ AVFilterContext ;
typedef  TYPE_3__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_OPTION_NOT_FOUND ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_3__* av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char const*,...) ; 
 char* av_strdup (char const*) ; 
 int avfilter_init_dict (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int process_options (TYPE_2__*,int /*<<< orphan*/ **,char const*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

int avfilter_init_str(AVFilterContext *filter, const char *args)
{
    AVDictionary *options = NULL;
    AVDictionaryEntry *e;
    int ret = 0;

    if (args && *args) {
        if (!filter->filter->priv_class) {
            av_log(filter, AV_LOG_ERROR, "This filter does not take any "
                   "options, but options were provided: %s.\n", args);
            return AVERROR(EINVAL);
        }

#if FF_API_OLD_FILTER_OPTS_ERROR
            if (   !strcmp(filter->filter->name, "format")     ||
                   !strcmp(filter->filter->name, "noformat")   ||
                   !strcmp(filter->filter->name, "frei0r")     ||
                   !strcmp(filter->filter->name, "frei0r_src") ||
                   !strcmp(filter->filter->name, "ocv")        ||
                   !strcmp(filter->filter->name, "pan")        ||
                   !strcmp(filter->filter->name, "pp")         ||
                   !strcmp(filter->filter->name, "aevalsrc")) {
            /* a hack for compatibility with the old syntax
             * replace colons with |s */
            char *copy = av_strdup(args);
            char *p    = copy;
            int nb_leading = 0; // number of leading colons to skip
            int deprecated = 0;

            if (!copy) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }

            if (!strcmp(filter->filter->name, "frei0r") ||
                !strcmp(filter->filter->name, "ocv"))
                nb_leading = 1;
            else if (!strcmp(filter->filter->name, "frei0r_src"))
                nb_leading = 3;

            while (nb_leading--) {
                p = strchr(p, ':');
                if (!p) {
                    p = copy + strlen(copy);
                    break;
                }
                p++;
            }

            deprecated = strchr(p, ':') != NULL;

            if (!strcmp(filter->filter->name, "aevalsrc")) {
                deprecated = 0;
                while ((p = strchr(p, ':')) && p[1] != ':') {
                    const char *epos = strchr(p + 1, '=');
                    const char *spos = strchr(p + 1, ':');
                    const int next_token_is_opt = epos && (!spos || epos < spos);
                    if (next_token_is_opt) {
                        p++;
                        break;
                    }
                    /* next token does not contain a '=', assume a channel expression */
                    deprecated = 1;
                    *p++ = '|';
                }
                if (p && *p == ':') { // double sep '::' found
                    deprecated = 1;
                    memmove(p, p + 1, strlen(p));
                }
            } else
            while ((p = strchr(p, ':')))
                *p++ = '|';

            if (deprecated) {
                av_log(filter, AV_LOG_ERROR, "This syntax is deprecated. Use "
                       "'|' to separate the list items ('%s' instead of '%s')\n",
                       copy, args);
                ret = AVERROR(EINVAL);
            } else {
                ret = process_options(filter, &options, copy);
            }
            av_freep(&copy);

            if (ret < 0)
                goto fail;
        } else
#endif
        {
            ret = process_options(filter, &options, args);
            if (ret < 0)
                goto fail;
        }
    }

    ret = avfilter_init_dict(filter, &options);
    if (ret < 0)
        goto fail;

    if ((e = av_dict_get(options, "", NULL, AV_DICT_IGNORE_SUFFIX))) {
        av_log(filter, AV_LOG_ERROR, "No such option: %s.\n", e->key);
        ret = AVERROR_OPTION_NOT_FOUND;
        goto fail;
    }

fail:
    av_dict_free(&options);

    return ret;
}