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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  addr_conv_t ;

/* Variables and functions */

__attribute__((used)) static size_t scribble_len(int num)
{
	size_t len;

	len = sizeof(struct page *) * (num+2) + sizeof(addr_conv_t) * (num+2);

	return len;
}