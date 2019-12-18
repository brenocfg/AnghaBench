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
 int ZFCP_DBF_TAG_SIZE ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void zfcp_dbf_tag(char **p, const char *label, const char *tag)
{
	int i;

	*p += sprintf(*p, "%-24s", label);
	for (i = 0; i < ZFCP_DBF_TAG_SIZE; i++)
		*p += sprintf(*p, "%c", tag[i]);
	*p += sprintf(*p, "\n");
}