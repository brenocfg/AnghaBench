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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {unsigned char* buf; int buf_size; void* cookie; int lock; int /*<<< orphan*/  read; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int vfwscanf (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wstring_read ; 

int vswscanf(const wchar_t *restrict s, const wchar_t *restrict fmt, va_list ap)
{
	unsigned char buf[256];
	FILE f = {
		.buf = buf, .buf_size = sizeof buf,
		.cookie = (void *)s,
		.read = wstring_read, .lock = -1
	};
	return vfwscanf(&f, fmt, ap);
}