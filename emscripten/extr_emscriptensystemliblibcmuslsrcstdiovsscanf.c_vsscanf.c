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
struct TYPE_3__ {void* buf; void* cookie; int lock; int /*<<< orphan*/  read; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  do_read ; 
 int vfscanf (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

int vsscanf(const char *restrict s, const char *restrict fmt, va_list ap)
{
	FILE f = {
		.buf = (void *)s, .cookie = (void *)s,
		.read = do_read, .lock = -1
	};
	return vfscanf(&f, fmt, ap);
}