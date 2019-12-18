#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
struct vacm_access {scalar_t__ sec_model; scalar_t__ sec_level; int /*<<< orphan*/  ctx_prefix; TYPE_1__* group; } ;
struct asn_oid {int dummy; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  groupname; } ;

/* Variables and functions */
 int SNMP_ADM_STR32_SIZ ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vacm_access_rule_index_decode (struct asn_oid const*,int /*<<< orphan*/ ,char*,char*,scalar_t__*,scalar_t__*) ; 
 struct vacm_access* vacm_first_access_rule () ; 
 struct vacm_access* vacm_next_access_rule (struct vacm_access*) ; 

struct vacm_access *
vacm_get_access_rule(const struct asn_oid *oid, uint sub)
{
	int32_t smodel, slevel;
	char gname[SNMP_ADM_STR32_SIZ], prefix[SNMP_ADM_STR32_SIZ];
	struct vacm_access *acl;

	if (vacm_access_rule_index_decode(oid, sub, gname, prefix, &smodel,
	    &slevel) < 0)
		return (NULL);

	for (acl = vacm_first_access_rule(); acl != NULL;
	    acl = vacm_next_access_rule(acl))
		if (strcmp(gname, acl->group->groupname) == 0 &&
		    strcmp(prefix, acl->ctx_prefix) == 0 &&
		    smodel == acl->sec_model && slevel == acl->sec_level)
			return (acl);

	return (NULL);
}