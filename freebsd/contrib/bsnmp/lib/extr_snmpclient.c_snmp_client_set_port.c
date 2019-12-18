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
struct snmp_client {char* cport; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int
snmp_client_set_port(struct snmp_client *cl, const char *p)
{
	char *np;

	if (p == NULL) {
		if (cl->cport != NULL)
			free(cl->cport);
		cl->cport = NULL;
	} else {
		if ((np = malloc(strlen(p) + 1)) == NULL)
			return (-1);
		strcpy(np, p);
		if (cl->cport != NULL)
			free(cl->cport);
		cl->cport = np;
	}
	return (0);
}