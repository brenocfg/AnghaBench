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
 int P_CHOICE ; 
 int P_COMMENT ; 
 int P_DEFAULT ; 
 int P_MENU ; 
 int P_PROMPT ; 
 int P_UNKNOWN ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

const char *dbg_print_ptype(int val)
{
	static char buf[256];

	bzero(buf, 256);

	if (val == P_UNKNOWN)
		strcpy(buf, "unknown");
	if (val == P_PROMPT)
		strcpy(buf, "prompt");
	if (val == P_COMMENT)
		strcpy(buf, "comment");
	if (val == P_MENU)
		strcpy(buf, "menu");
	if (val == P_DEFAULT)
		strcpy(buf, "default");
	if (val == P_CHOICE)
		strcpy(buf, "choice");

#ifdef DEBUG
	printf("%s", buf);
#endif

	return buf;
}