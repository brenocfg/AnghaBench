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
struct pfi_kif {char* pfik_name; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

int
pfi_skip_if(const char *filter, struct pfi_kif *p)
{
	int	n;

	if (filter == NULL || !*filter)
		return (0);
	if (strcmp(p->pfik_name, filter) == 0)
		return (0);	/* exact match */
	n = strlen(filter);
	if (n < 1 || n >= IFNAMSIZ)
		return (1);	/* sanity check */
	if (filter[n-1] >= '0' && filter[n-1] <= '9')
		return (1);	/* only do exact match in that case */
	if (strncmp(p->pfik_name, filter, n))
		return (1);	/* prefix doesn't match */
	return (p->pfik_name[n] < '0' || p->pfik_name[n] > '9');
}