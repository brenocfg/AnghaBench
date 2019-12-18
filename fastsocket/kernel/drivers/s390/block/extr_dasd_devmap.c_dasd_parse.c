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
 int /*<<< orphan*/  DBF_ALERT ; 
 int /*<<< orphan*/  DBF_EVENT (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 char** dasd ; 
 char* dasd_parse_next_element (char*) ; 

int
dasd_parse(void)
{
	int rc, i;
	char *parsestring;

	rc = 0;
	for (i = 0; i < 256; i++) {
		if (dasd[i] == NULL)
			break;
		parsestring = dasd[i];
		/* loop over the comma separated list in the parsestring */
		while (*parsestring) {
			parsestring = dasd_parse_next_element(parsestring);
			if(IS_ERR(parsestring)) {
				rc = PTR_ERR(parsestring);
				break;
			}
		}
		if (rc) {
			DBF_EVENT(DBF_ALERT, "%s", "invalid range found");
			break;
		}
	}
	return rc;
}