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
typedef  size_t uint32_t ;
typedef  size_t uint ;
struct asn_oid {size_t* subs; } ;
typedef  char int32_t ;

/* Variables and functions */
 size_t SNMP_ADM_STR32_SIZ ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
vacm_access_rule_index_decode(const struct asn_oid *oid, uint sub, char *gname,
    char *cprefix, int32_t *smodel, int32_t *slevel)
{
	uint32_t i;

	if (oid->subs[sub] >= SNMP_ADM_STR32_SIZ)
		return (-1);

	for (i = 0; i < oid->subs[sub]; i++)
		gname[i] = oid->subs[sub + i + 1];
	gname[i] = '\0';
	sub += strlen(gname) + 1;

	if (oid->subs[sub] >= SNMP_ADM_STR32_SIZ)
		return (-1);

	for (i = 0; i < oid->subs[sub]; i++)
		cprefix[i] = oid->subs[sub + i + 1];
	cprefix[i] = '\0';
	sub += strlen(cprefix) + 1;

	*smodel = oid->subs[sub++];
	*slevel = oid->subs[sub];

	return (0);
}