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
struct TYPE_3__ {int lock; size_t buf_size; scalar_t__* wend; scalar_t__* wpos; scalar_t__* wbase; scalar_t__* buf; int /*<<< orphan*/  write; int /*<<< orphan*/  lbf; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EOF ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int INT_MAX ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  sn_write ; 
 int vfiprintf (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

int vsniprintf(char *restrict s, size_t n, const char *restrict fmt, va_list ap)
{
	int r;
	char b;
	FILE f = { .lbf = EOF, .write = sn_write, .lock = -1 };

	if (n-1 > INT_MAX-1) {
		if (n) {
			errno = EOVERFLOW;
			return -1;
		}
		s = &b;
		n = 1;
	}

	/* Ensure pointers don't wrap if "infinite" n is passed in */
	if (n > (char *)0+SIZE_MAX-s-1) n = (char *)0+SIZE_MAX-s-1;
	f.buf_size = n;
	f.buf = f.wpos = (void *)s;
	f.wbase = f.wend = (void *)(s+n);
	r = vfiprintf(&f, fmt, ap);

	/* Null-terminate, overwriting last char if dest buffer is full */
	if (n) f.wpos[-(f.wpos == f.wend)] = 0;
	return r;
}