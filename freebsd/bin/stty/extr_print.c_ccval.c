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
struct cchar {scalar_t__ sub; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ VMIN ; 
 scalar_t__ VTIME ; 
 int _POSIX_VDISABLE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
ccval(struct cchar *p, int c)
{
	static char buf[5];
	char *bp;

	if (p->sub == VMIN || p->sub == VTIME) {
		(void)snprintf(buf, sizeof(buf), "%d", c);
		return (buf);
	}
	if (c == _POSIX_VDISABLE)
		return ("<undef>");
	bp = buf;
	if (c & 0200) {
		*bp++ = 'M';
		*bp++ = '-';
		c &= 0177;
	}
	if (c == 0177) {
		*bp++ = '^';
		*bp++ = '?';
	}
	else if (c < 040) {
		*bp++ = '^';
		*bp++ = c + '@';
	}
	else
		*bp++ = c;
	*bp = '\0';
	return (buf);
}