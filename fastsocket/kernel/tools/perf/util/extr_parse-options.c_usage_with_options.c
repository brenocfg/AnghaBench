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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exit_browser (int) ; 
 int /*<<< orphan*/  usage_with_options_internal (char const* const*,struct option const*,int /*<<< orphan*/ ) ; 

void usage_with_options(const char * const *usagestr,
			const struct option *opts)
{
	exit_browser(false);
	usage_with_options_internal(usagestr, opts, 0);
	exit(129);
}