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
 int /*<<< orphan*/  ctmainbench ; 
 int /*<<< orphan*/  ctmaintest ; 
 int readtokens () ; 
 int report (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runallbench (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runalltest (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  writetokens (int) ; 

int
main(int argc, char **argv)
{
    int n = readtokens();
    runalltest(ctmaintest, n);
    writetokens(n);
    int code = report(ctmaintest);
    if (code != 0) {
        return code;
    }
    if (argc == 2 && strcmp(argv[1], "-b") == 0) {
        runallbench(ctmainbench);
    }
    return 0;
}