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
typedef  void* iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int* charmaps ; 
 int /*<<< orphan*/  errno ; 
 size_t find_charmap (char const*) ; 

iconv_t iconv_open(const char *to, const char *from)
{
	size_t f, t;

	if ((t = find_charmap(to))==-1
	 || (f = find_charmap(from))==-1
	 || (charmaps[t] >= 0320)) {
		errno = EINVAL;
		return (iconv_t)-1;
	}

	return (void *)(f<<16 | t);
}