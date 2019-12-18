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
struct super_block {int dummy; } ;
struct security_mnt_opts {int /*<<< orphan*/  num_mnt_opts; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cap_sb_set_mnt_opts(struct super_block *sb,
			       struct security_mnt_opts *opts)
{
	if (unlikely(opts->num_mnt_opts))
		return -EOPNOTSUPP;
	return 0;
}