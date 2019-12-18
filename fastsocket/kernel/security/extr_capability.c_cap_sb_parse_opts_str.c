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
struct security_mnt_opts {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int cap_sb_parse_opts_str(char *options, struct security_mnt_opts *opts)
{
	return 0;
}