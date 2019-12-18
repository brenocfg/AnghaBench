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
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*,float const) ; 
 int validate_float_option (float,float const*,int) ; 

__attribute__((used)) static void validate_mix_level(void *log_ctx, const char *opt_name,
                               float *opt_param, const float *list,
                               int list_size, int default_value, int min_value,
                               int *ctx_param)
{
    int mixlev = validate_float_option(*opt_param, list, list_size);
    if (mixlev < min_value) {
        mixlev = default_value;
        if (*opt_param >= 0.0) {
            av_log(log_ctx, AV_LOG_WARNING, "requested %s is not valid. using "
                   "default value: %0.3f\n", opt_name, list[mixlev]);
        }
    }
    *opt_param = list[mixlev];
    *ctx_param = mixlev;
}