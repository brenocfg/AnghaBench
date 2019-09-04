#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  va_list ;
struct cookie {size_t member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_5__ {int buf_size; unsigned char* buf; int lock; struct cookie* cookie; int /*<<< orphan*/  (* write ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lbf; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EOF ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sw_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfwprintf (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int vswprintf(wchar_t *restrict s, size_t n, const wchar_t *restrict fmt, va_list ap)
{
	int r;
	FILE f;
	unsigned char buf[256];
	struct cookie c = { s, n-1 };

	memset(&f, 0, sizeof(FILE));
	f.lbf = EOF;
	f.write = sw_write;
	f.buf_size = sizeof buf;
	f.buf = buf;
	f.lock = -1;
	f.cookie = &c;
	if (!n) {
		return -1;
	} else if (n > INT_MAX) {
		errno = EOVERFLOW;
		return -1;
	}
	r = vfwprintf(&f, fmt, ap);
	sw_write(&f, 0, 0);
	return r>=n ? -1 : r;
}