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
 int __MAX_CSSID ; 
 int __MAX_SSID ; 
 int __MAX_SUBCHANNEL ; 
 int /*<<< orphan*/  pr_warning (char*,char*) ; 
 int pure_hex (char**,unsigned int*,int,int,int) ; 
 int simple_strtoul (char*,char**,int) ; 

__attribute__((used)) static int parse_busid(char *str, unsigned int *cssid, unsigned int *ssid,
		       unsigned int *devno, int msgtrigger)
{
	char *str_work;
	int val, rc, ret;

	rc = 1;

	if (*str == '\0')
		goto out;

	/* old style */
	str_work = str;
	val = simple_strtoul(str, &str_work, 16);

	if (*str_work == '\0') {
		if (val <= __MAX_SUBCHANNEL) {
			*devno = val;
			*ssid = 0;
			*cssid = 0;
			rc = 0;
		}
		goto out;
	}

	/* new style */
	str_work = str;
	ret = pure_hex(&str_work, cssid, 1, 2, __MAX_CSSID);
	if (ret || (str_work[0] != '.'))
		goto out;
	str_work++;
	ret = pure_hex(&str_work, ssid, 1, 1, __MAX_SSID);
	if (ret || (str_work[0] != '.'))
		goto out;
	str_work++;
	ret = pure_hex(&str_work, devno, 4, 4, __MAX_SUBCHANNEL);
	if (ret || (str_work[0] != '\0'))
		goto out;

	rc = 0;
out:
	if (rc && msgtrigger)
		pr_warning("%s is not a valid device for the cio_ignore "
			   "kernel parameter\n", str);

	return rc;
}