#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; int len; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */

__attribute__((used)) static unsigned name_to_int(struct dentry *dentry)
{
	const char *name = dentry->d_name.name;
	int len = dentry->d_name.len;
	unsigned n = 0;

	if (len > 1 && *name == '0')
		goto out;
	while (len-- > 0) {
		unsigned c = *name++ - '0';
		if (c > 9)
			goto out;
		if (n >= (~0U-9)/10)
			goto out;
		n *= 10;
		n += c;
	}
	return n;
out:
	return ~0U;
}