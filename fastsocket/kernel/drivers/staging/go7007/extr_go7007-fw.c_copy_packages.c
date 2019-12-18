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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16p (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int copy_packages(__le16 *dest, u16 *src, int pkg_cnt, int space)
{
	int i, cnt = pkg_cnt * 32;

	if (space < cnt)
		return -1;

	for (i = 0; i < cnt; ++i)
		dest[i] = cpu_to_le16p(src + i);

	return cnt;
}