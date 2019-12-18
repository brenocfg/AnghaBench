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
struct path {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  TOMOYO_TYPE_TRUNCATE_ACL ; 
 int tomoyo_check_1path_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  tomoyo_domain () ; 

__attribute__((used)) static int tomoyo_path_truncate(struct path *path, loff_t length,
				unsigned int time_attrs)
{
	return tomoyo_check_1path_perm(tomoyo_domain(),
				       TOMOYO_TYPE_TRUNCATE_ACL,
				       path);
}