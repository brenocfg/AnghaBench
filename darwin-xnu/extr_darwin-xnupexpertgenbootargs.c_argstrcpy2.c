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
 int /*<<< orphan*/  isargsep (char) ; 

__attribute__((used)) static int
argstrcpy2(
	char *from,
	char *to,
	unsigned maxlen)
{
	unsigned int i = 0;

	while (!isargsep(*from) && i < maxlen) {
		i++;
		*to++ = *from++;
	}
	*to = 0;
	return(i);
}