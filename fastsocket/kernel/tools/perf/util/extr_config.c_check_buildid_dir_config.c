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
struct buildid_dir_config {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  buildid_dir ; 
 int /*<<< orphan*/  buildid_dir_command_config ; 
 int /*<<< orphan*/  perf_config (int /*<<< orphan*/ ,struct buildid_dir_config*) ; 

__attribute__((used)) static void check_buildid_dir_config(void)
{
	struct buildid_dir_config c;
	c.dir = buildid_dir;
	perf_config(buildid_dir_command_config, &c);
}