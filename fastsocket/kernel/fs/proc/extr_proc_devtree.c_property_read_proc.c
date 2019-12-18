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
struct property {scalar_t__ length; scalar_t__ value; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int property_read_proc(char *page, char **start, off_t off,
			      int count, int *eof, void *data)
{
	struct property *pp = data;
	int n;

	if (off >= pp->length) {
		*eof = 1;
		return 0;
	}
	n = pp->length - off;
	if (n > count)
		n = count;
	else
		*eof = 1;
	memcpy(page, (char *)pp->value + off, n);
	*start = page;
	return n;
}