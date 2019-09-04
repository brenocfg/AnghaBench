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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {int fd; void* buf; int lock; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  write; int /*<<< orphan*/  lbf; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EOF ; 
 int vfprintf (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrap_write ; 

int vdprintf(int fd, const char *restrict fmt, va_list ap)
{
	FILE f = {
		.fd = fd, .lbf = EOF, .write = wrap_write,
		.buf = (void *)fmt, .buf_size = 0,
		.lock = -1
	};
	return vfprintf(&f, fmt, ap);
}