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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 size_t snprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t format_array(char *buf, size_t bufsize, const char *fmt,
			   u32 *array, unsigned array_size)
{
	size_t ret = 0;
	unsigned i;

	for(i = 0; i < array_size; i++) {
		size_t len;

		len = snprintf(buf, bufsize, fmt, array[i]);
		len++;	/* ' ' or '\n' */
		ret += len;

		if (buf) {
			buf += len;
			bufsize -= len;
			buf[-1] = (i == array_size-1) ? '\n' : ' ';
		}
	}

	ret++;		/* \0 */
	if (buf)
		*buf = '\0';

	return ret;
}