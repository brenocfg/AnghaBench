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
struct passwd {char* pw_name; char* pw_passwd; int pw_uid; int pw_gid; char* pw_gecos; char* pw_dir; char* pw_shell; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*,char*,int,int,char*,char*,char*) ; 

int putpwent(const struct passwd *pw, FILE *f)
{
	return fprintf(f, "%s:%s:%d:%d:%s:%s:%s\n",
		pw->pw_name, pw->pw_passwd, pw->pw_uid, pw->pw_gid,
		pw->pw_gecos, pw->pw_dir, pw->pw_shell)<0 ? -1 : 0;
}