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
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  OPT_INT64 ; 
 int /*<<< orphan*/  parse_number_or_die (char const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_width ; 

__attribute__((used)) static int opt_width(void *optctx, const char *opt, const char *arg)
{
    screen_width = parse_number_or_die(opt, arg, OPT_INT64, 1, INT_MAX);
    return 0;
}