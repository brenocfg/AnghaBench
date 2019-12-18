#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  pe_fd; } ;
typedef  TYPE_1__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,size_t) ; 

int
libpe_pad(PE *pe, size_t pad)
{
	char tmp[128];
	size_t s;

	memset(tmp, 0, sizeof(tmp));
	for (; pad > 0; pad -= s) {
		s = pad > sizeof(tmp) ? sizeof(tmp) : pad;
		if (write(pe->pe_fd, tmp, s) != (ssize_t) s) {
			errno = EIO;
			return (-1);
		}
	}

	return (0);
}