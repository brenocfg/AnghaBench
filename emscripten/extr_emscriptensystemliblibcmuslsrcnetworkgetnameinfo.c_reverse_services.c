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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  __fclose_ca (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * __fopen_rb_ca (char*,int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 unsigned long strtoul (char*,char**,int) ; 

__attribute__((used)) static void reverse_services(char *buf, int port, int dgram)
{
	unsigned long svport;
	char line[128], *p, *z;
	unsigned char _buf[1032];
	FILE _f, *f = __fopen_rb_ca("/etc/services", &_f, _buf, sizeof _buf);
	if (!f) return;
	while (fgets(line, sizeof line, f)) {
		if ((p=strchr(line, '#'))) *p++='\n', *p=0;

		for (p=line; *p && !isspace(*p); p++);
		if (!*p) continue;
		*p++ = 0;
		svport = strtoul(p, &z, 10);

		if (svport != port || z==p) continue;
		if (dgram && strncmp(z, "/udp", 4)) continue;
		if (!dgram && strncmp(z, "/tcp", 4)) continue;
		if (p-line > 32) continue;

		memcpy(buf, line, p-line);
		break;
	}
	__fclose_ca(f);
}