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
struct loadedfile {size_t len; char* buf; scalar_t__ used; } ;

/* Variables and functions */
 scalar_t__ TRUE ; 

__attribute__((used)) static char *
loadedfile_nextbuf(void *x, size_t *len)
{
	struct loadedfile *lf = x;

	if (lf->used) {
		return NULL;
	}
	lf->used = TRUE;
	*len = lf->len;
	return lf->buf;
}