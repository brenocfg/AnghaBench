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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int CTL_KERN ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
act_getkernint(int id)
{
	int mib[2];
	size_t len;
	u_long value;
	char *string;

	mib[0] = CTL_KERN;
	mib[1] = id;
	len = sizeof(value);
	if (sysctl(mib, 2, &value, &len, NULL, 0) != 0)
		return (NULL);

	if ((string = malloc(20)) == NULL)
		return (NULL);
	sprintf(string, "%lu", value);
	return (string);
}