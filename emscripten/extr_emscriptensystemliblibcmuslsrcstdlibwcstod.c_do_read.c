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
typedef  int wchar_t ;
struct TYPE_3__ {int* cookie; size_t buf_size; int* buf; int* rpos; int* rend; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */

__attribute__((used)) static size_t do_read(FILE *f, unsigned char *buf, size_t len)
{
	size_t i;
	const wchar_t *wcs = f->cookie;

	if (!wcs[0]) wcs=L"@";
	for (i=0; i<f->buf_size && wcs[i]; i++)
		f->buf[i] = wcs[i] < 128 ? wcs[i] : '@';
	f->rpos = f->buf;
	f->rend = f->buf + i;
	f->cookie = (void *)(wcs+i);

	if (i && len) {
		*buf = *f->rpos++;
		return 1;
	}
	return 0;
}