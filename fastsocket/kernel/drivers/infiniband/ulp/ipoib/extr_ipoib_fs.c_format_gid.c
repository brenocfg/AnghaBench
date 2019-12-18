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
union ib_gid {scalar_t__ raw; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ sprintf (char*,char*,int) ; 

__attribute__((used)) static void format_gid(union ib_gid *gid, char *buf)
{
	int i, n;

	for (n = 0, i = 0; i < 8; ++i) {
		n += sprintf(buf + n, "%x",
			     be16_to_cpu(((__be16 *) gid->raw)[i]));
		if (i < 7)
			buf[n++] = ':';
	}
}