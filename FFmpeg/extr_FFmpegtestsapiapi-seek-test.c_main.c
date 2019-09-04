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
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ seek_test (char*,char*,char*) ; 

int main(int argc, char **argv)
{
    if (argc < 4) {
        av_log(NULL, AV_LOG_ERROR, "Incorrect input\n");
        return 1;
    }

    if (seek_test(argv[1], argv[2], argv[3]) != 0)
        return 1;

    return 0;
}