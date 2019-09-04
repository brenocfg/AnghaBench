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

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 unsigned int AV_OPT_FLAG_IMPLICIT_KEY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_get_token (char const**,char const*) ; 
 int get_key (char const**,char const*,char**) ; 

int av_opt_get_key_value(const char **ropts,
                         const char *key_val_sep, const char *pairs_sep,
                         unsigned flags,
                         char **rkey, char **rval)
{
    int ret;
    char *key = NULL, *val;
    const char *opts = *ropts;

    if ((ret = get_key(&opts, key_val_sep, &key)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_KEY))
        return AVERROR(EINVAL);
    if (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(key);
        return AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = key;
    *rval  = val;
    return 0;
}