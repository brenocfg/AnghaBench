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
struct subprocess_info {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void argv_cleanup(struct subprocess_info *info)
{
	argv_free(info->argv);
}