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

/* Variables and functions */
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static void
advance(char **p)
{
	char *ep = *p;
	while (*ep && !isspace((unsigned char)*ep))
		ep++;
	while (*ep && isspace((unsigned char)*ep))
		*ep++ = '\0';
	*p = ep;
}