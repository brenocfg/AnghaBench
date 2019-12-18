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
 int /*<<< orphan*/  errno ; 
 char const* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static __attribute__((__format_arg__(3))) const char *
expandm(char *buf, size_t len, const char *fmt) 
{
	char *p;
	size_t r;

	if ((p = strstr(fmt, "%m")) == NULL)
		return fmt;

	r = (size_t)(p - fmt);
	if (r >= len)
		return fmt;

	strlcpy(buf, fmt, r + 1);
	strlcat(buf, strerror(errno), len);
	strlcat(buf, fmt + r + 2, len);

	return buf;
}