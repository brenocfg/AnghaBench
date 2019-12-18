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
typedef  int /*<<< orphan*/  uids ;
typedef  int uid_t ;
struct passwd {char* pw_name; } ;

/* Variables and functions */
 struct passwd* getpwuid (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char *
getuname(uid_t uid)
{
	struct passwd *pw;
	static char uids[10];

	if ((pw = getpwuid(uid)) == NULL) {
		(void)snprintf(uids, sizeof(uids), "%u", uid);
		return (uids);
	} else
		return (pw->pw_name);
}