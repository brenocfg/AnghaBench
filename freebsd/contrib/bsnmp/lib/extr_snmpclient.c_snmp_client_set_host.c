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
struct snmp_client {char* chost; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int
snmp_client_set_host(struct snmp_client *cl, const char *h)
{
	char *np;

	if (h == NULL) {
		if (cl->chost != NULL)
			free(cl->chost);
		cl->chost = NULL;
	} else {
		if ((np = malloc(strlen(h) + 1)) == NULL)
			return (-1);
		strcpy(np, h);
		if (cl->chost != NULL)
			free(cl->chost);
		cl->chost = np;
	}
	return (0);
}