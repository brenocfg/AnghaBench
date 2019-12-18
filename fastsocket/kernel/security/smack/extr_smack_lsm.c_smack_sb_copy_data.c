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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SMK_FSDEFAULT ; 
 int /*<<< orphan*/  SMK_FSFLOOR ; 
 int /*<<< orphan*/  SMK_FSHAT ; 
 int /*<<< orphan*/  SMK_FSROOT ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smack_sb_copy_data(char *orig, char *smackopts)
{
	char *cp, *commap, *otheropts, *dp;

	otheropts = (char *)get_zeroed_page(GFP_KERNEL);
	if (otheropts == NULL)
		return -ENOMEM;

	for (cp = orig, commap = orig; commap != NULL; cp = commap + 1) {
		if (strstr(cp, SMK_FSDEFAULT) == cp)
			dp = smackopts;
		else if (strstr(cp, SMK_FSFLOOR) == cp)
			dp = smackopts;
		else if (strstr(cp, SMK_FSHAT) == cp)
			dp = smackopts;
		else if (strstr(cp, SMK_FSROOT) == cp)
			dp = smackopts;
		else
			dp = otheropts;

		commap = strchr(cp, ',');
		if (commap != NULL)
			*commap = '\0';

		if (*dp != '\0')
			strcat(dp, ",");
		strcat(dp, cp);
	}

	strcpy(orig, otheropts);
	free_page((unsigned long)otheropts);

	return 0;
}