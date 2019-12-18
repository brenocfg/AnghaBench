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
struct _ddebug {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int _DPRINTK_FLAGS_PRINT ; 

__attribute__((used)) static char *ddebug_describe_flags(struct _ddebug *dp, char *buf,
				    size_t maxlen)
{
	char *p = buf;

	BUG_ON(maxlen < 4);
	if (dp->flags & _DPRINTK_FLAGS_PRINT)
		*p++ = 'p';
	if (p == buf)
		*p++ = '-';
	*p = '\0';

	return buf;
}