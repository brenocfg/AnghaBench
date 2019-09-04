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
typedef  unsigned long LADSPA_Data ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int av_sscanf (char const*,char*,unsigned long*) ; 
 int set_control (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static int process_command(AVFilterContext *ctx, const char *cmd, const char *args,
                           char *res, int res_len, int flags)
{
    LADSPA_Data value;
    unsigned long port;

    if (av_sscanf(cmd, "c%ld", &port) + av_sscanf(args, "%f", &value) != 2)
        return AVERROR(EINVAL);

    return set_control(ctx, port, value);
}