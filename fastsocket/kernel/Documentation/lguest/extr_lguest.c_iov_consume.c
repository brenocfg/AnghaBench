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
struct iovec {unsigned int iov_len; unsigned int iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void iov_consume(struct iovec iov[], unsigned num_iov, unsigned len)
{
	unsigned int i;

	for (i = 0; i < num_iov; i++) {
		unsigned int used;

		used = iov[i].iov_len < len ? iov[i].iov_len : len;
		iov[i].iov_base += used;
		iov[i].iov_len -= used;
		len -= used;
	}
	assert(len == 0);
}