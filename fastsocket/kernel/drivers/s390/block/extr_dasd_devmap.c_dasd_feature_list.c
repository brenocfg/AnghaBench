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
 int DASD_FEATURE_DEFAULT ; 
 int DASD_FEATURE_ERPLOG ; 
 int DASD_FEATURE_FAILFAST ; 
 int DASD_FEATURE_READONLY ; 
 int DASD_FEATURE_USEDIAG ; 
 int DASD_FEATURE_USERAW ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int
dasd_feature_list(char *str, char **endp)
{
	int features, len, rc;

	rc = 0;
	if (*str != '(') {
		*endp = str;
		return DASD_FEATURE_DEFAULT;
	}
	str++;
	features = 0;

	while (1) {
		for (len = 0;
		     str[len] && str[len] != ':' && str[len] != ')'; len++);
		if (len == 2 && !strncmp(str, "ro", 2))
			features |= DASD_FEATURE_READONLY;
		else if (len == 4 && !strncmp(str, "diag", 4))
			features |= DASD_FEATURE_USEDIAG;
		else if (len == 3 && !strncmp(str, "raw", 3))
			features |= DASD_FEATURE_USERAW;
		else if (len == 6 && !strncmp(str, "erplog", 6))
			features |= DASD_FEATURE_ERPLOG;
		else if (len == 8 && !strncmp(str, "failfast", 8))
			features |= DASD_FEATURE_FAILFAST;
		else {
			pr_warning("%*s is not a supported device option\n",
				   len, str);
			rc = -EINVAL;
		}
		str += len;
		if (*str != ':')
			break;
		str++;
	}
	if (*str != ')') {
		pr_warning("A closing parenthesis ')' is missing in the "
			   "dasd= parameter\n");
		rc = -EINVAL;
	} else
		str++;
	*endp = str;
	if (rc != 0)
		return rc;
	return features;
}