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
struct iovec {scalar_t__ iov_len; } ;

/* Variables and functions */

__attribute__((used)) static bool iov_empty(const struct iovec iov[], unsigned int num_iov)
{
	unsigned int i;

	for (i = 0; i < num_iov; i++)
		if (iov[i].iov_len)
			return false;
	return true;
}