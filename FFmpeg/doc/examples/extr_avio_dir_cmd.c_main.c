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
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_log_set_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avformat_network_deinit () ; 
 int /*<<< orphan*/  avformat_network_init () ; 
 int del_op (char*) ; 
 int list_op (char*) ; 
 int move_op (char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
    const char *op = NULL;
    int ret;

    av_log_set_level(AV_LOG_DEBUG);

    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    avformat_network_init();

    op = argv[1];
    if (strcmp(op, "list") == 0) {
        if (argc < 3) {
            av_log(NULL, AV_LOG_INFO, "Missing argument for list operation.\n");
            ret = AVERROR(EINVAL);
        } else {
            ret = list_op(argv[2]);
        }
    } else if (strcmp(op, "del") == 0) {
        if (argc < 3) {
            av_log(NULL, AV_LOG_INFO, "Missing argument for del operation.\n");
            ret = AVERROR(EINVAL);
        } else {
            ret = del_op(argv[2]);
        }
    } else if (strcmp(op, "move") == 0) {
        if (argc < 4) {
            av_log(NULL, AV_LOG_INFO, "Missing argument for move operation.\n");
            ret = AVERROR(EINVAL);
        } else {
            ret = move_op(argv[2], argv[3]);
        }
    } else {
        av_log(NULL, AV_LOG_INFO, "Invalid operation %s\n", op);
        ret = AVERROR(EINVAL);
    }

    avformat_network_deinit();

    return ret < 0 ? 1 : 0;
}