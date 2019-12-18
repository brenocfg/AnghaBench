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
typedef  size_t int32_t ;

/* Variables and functions */
 size_t SNMP_ADM_STR32_SIZ ; 

__attribute__((used)) static int
vacm_user_index_decode(const struct asn_oid *oid, uint sub,
    int32_t *smodel, char *uname)
{
	uint32_t i;

	*smodel = oid->subs[sub++];

	if (oid->subs[sub] >= SNMP_ADM_STR32_SIZ)
		return (-1);

	for (i = 0; i < oid->subs[sub]; i++)
		uname[i] = oid->subs[sub + i + 1];
	uname[i] = '\0';

	return (0);
}