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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  bad_path ; 
 char* cleanup_path (char*) ; 
 char* get_perf_dir () ; 
 int /*<<< orphan*/  is_dir_sep (char const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *perf_vsnpath(char *buf, size_t n, const char *fmt, va_list args)
{
	const char *perf_dir = get_perf_dir();
	size_t len;

	len = strlen(perf_dir);
	if (n < len + 1)
		goto bad;
	memcpy(buf, perf_dir, len);
	if (len && !is_dir_sep(perf_dir[len-1]))
		buf[len++] = '/';
	len += vsnprintf(buf + len, n - len, fmt, args);
	if (len >= n)
		goto bad;
	return cleanup_path(buf);
bad:
	strlcpy(buf, bad_path, n);
	return buf;
}