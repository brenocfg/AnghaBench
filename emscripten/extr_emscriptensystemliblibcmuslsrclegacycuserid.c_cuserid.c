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
struct passwd {char* pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  L_cuserid ; 
 int /*<<< orphan*/  geteuid () ; 
 scalar_t__ getpwuid_r (int /*<<< orphan*/ ,struct passwd*,void*,int,struct passwd**) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

char *cuserid(char *buf)
{
	struct passwd pw, *ppw;
	long pwb[256];
	if (getpwuid_r(geteuid(), &pw, (void *)pwb, sizeof pwb, &ppw))
		return 0;
	snprintf(buf, L_cuserid, "%s", pw.pw_name);
	return buf;
}