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
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AV_DICT_DONT_STRDUP_KEY ; 
 int AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int av_dict_set (int /*<<< orphan*/ **,char*,char*,int) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*) ; 
 int av_opt_get_key_value (char const**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,char**) ; 
 int /*<<< orphan*/  slave_opt_close ; 
 int /*<<< orphan*/  slave_opt_delim ; 
 int /*<<< orphan*/  slave_opt_open ; 
 scalar_t__ strspn (char const*,int /*<<< orphan*/ ) ; 

int ff_tee_parse_slave_options(void *log, char *slave,
                               AVDictionary **options, char **filename)
{
    const char *p;
    char *key, *val;
    int ret;

    if (!strspn(slave, slave_opt_open)) {
        *filename = slave;
        return 0;
    }
    p = slave + 1;
    if (strspn(p, slave_opt_close)) {
        *filename = (char *)p + 1;
        return 0;
    }
    while (1) {
        ret = av_opt_get_key_value(&p, "=", slave_opt_delim, 0, &key, &val);
        if (ret < 0) {
            av_log(log, AV_LOG_ERROR, "No option found near \"%s\"\n", p);
            goto fail;
        }
        ret = av_dict_set(options, key, val,
                          AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);
        if (ret < 0)
            goto fail;
        if (strspn(p, slave_opt_close))
            break;
        p++;
    }
    *filename = (char *)p + 1;
    return 0;

fail:
    av_dict_free(options);
    return ret;
}