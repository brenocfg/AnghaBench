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
struct psmouse {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  fsp_onpad_hscr (struct psmouse*,unsigned long) ; 
 scalar_t__ strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t fsp_attr_set_hscroll(struct psmouse *psmouse, void *data,
					const char *buf, size_t count)
{
	unsigned long val;

	if (strict_strtoul(buf, 10, &val) || val > 1)
		return -EINVAL;

	fsp_onpad_hscr(psmouse, val);

	return count;
}