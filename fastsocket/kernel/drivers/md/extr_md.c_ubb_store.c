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
struct md_rdev {int /*<<< orphan*/  badblocks; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  badblocks_store (int /*<<< orphan*/ *,char const*,size_t,int) ; 

__attribute__((used)) static ssize_t ubb_store(struct md_rdev *rdev, const char *page, size_t len)
{
	return badblocks_store(&rdev->badblocks, page, len, 1);
}