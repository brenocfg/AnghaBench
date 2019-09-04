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
 int /*<<< orphan*/  AV_OPT_FLAG_DECODING_PARAM ; 
 int /*<<< orphan*/  av_log_set_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_get_class () ; 
 int /*<<< orphan*/  avformat_get_class () ; 
 int /*<<< orphan*/  log_callback_help ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  show_help_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_help_options (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_usage () ; 

void show_help_default(const char *opt, const char *arg)
{
    av_log_set_callback(log_callback_help);
    show_usage();
    show_help_options(options, "Main options:", 0, 0, 0);
    printf("\n");

    show_help_children(avformat_get_class(), AV_OPT_FLAG_DECODING_PARAM);
    show_help_children(avcodec_get_class(), AV_OPT_FLAG_DECODING_PARAM);
}