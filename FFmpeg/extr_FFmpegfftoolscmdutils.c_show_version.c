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
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  SHOW_COPYRIGHT ; 
 int /*<<< orphan*/  SHOW_VERSION ; 
 int /*<<< orphan*/  av_log_set_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_callback_help ; 
 int /*<<< orphan*/  print_all_libs_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_program_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int show_version(void *optctx, const char *opt, const char *arg)
{
    av_log_set_callback(log_callback_help);
    print_program_info (SHOW_COPYRIGHT, AV_LOG_INFO);
    print_all_libs_info(SHOW_VERSION, AV_LOG_INFO);

    return 0;
}