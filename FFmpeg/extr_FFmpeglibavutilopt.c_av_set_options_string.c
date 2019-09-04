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
 int parse_key_value_pair (void*,char const**,char const*,char const*) ; 

int av_set_options_string(void *ctx, const char *opts,
                          const char *key_val_sep, const char *pairs_sep)
{
    int ret, count = 0;

    if (!opts)
        return 0;

    while (*opts) {
        if ((ret = parse_key_value_pair(ctx, &opts, key_val_sep, pairs_sep)) < 0)
            return ret;
        count++;

        if (*opts)
            opts++;
    }

    return count;
}