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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint ;
struct asn_oid {size_t* subs; } ;

/* Variables and functions */
 size_t SNMP_ADM_STR32_SIZ ; 
 size_t SNMP_ENGINE_ID_SIZ ; 

__attribute__((used)) static int
usm_user_index_decode(const struct asn_oid *oid, uint sub, uint8_t *engine,
    uint32_t *elen, char *uname)
{
	uint32_t i, nlen;
	int uname_off;

	if (oid->subs[sub] > SNMP_ENGINE_ID_SIZ)
		return (-1);

	for (i = 0; i < oid->subs[sub]; i++)
		engine[i] = oid->subs[sub + i + 1];
	*elen = i;

	uname_off = sub + oid->subs[sub] + 1;
	if ((nlen = oid->subs[uname_off]) >= SNMP_ADM_STR32_SIZ)
		return (-1);

	for (i = 0; i < nlen; i++)
		uname[i] = oid->subs[uname_off + i + 1];
	uname[nlen] = '\0';

	return (0);
}