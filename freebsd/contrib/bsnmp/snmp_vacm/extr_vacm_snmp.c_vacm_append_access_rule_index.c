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
typedef  size_t uint32_t ;
typedef  size_t uint ;
struct vacm_access {int* ctx_prefix; int sec_model; int sec_level; TYPE_1__* group; } ;
struct asn_oid {size_t len; int* subs; } ;
struct TYPE_2__ {int* groupname; } ;

/* Variables and functions */
 int strlen (int*) ; 

__attribute__((used)) static void
vacm_append_access_rule_index(struct asn_oid *oid, uint sub,
    const struct vacm_access *acl)
{
	uint32_t i;

	oid->len = sub + strlen(acl->group->groupname) +
	    strlen(acl->ctx_prefix) + 4;

	oid->subs[sub] = strlen(acl->group->groupname);
	for (i = 1; i <= strlen(acl->group->groupname); i++)
		oid->subs[sub + i] = acl->group->groupname[i - 1];
	sub += strlen(acl->group->groupname) + 1;

	oid->subs[sub] = strlen(acl->ctx_prefix);
	for (i = 1; i <= strlen(acl->ctx_prefix); i++)
		oid->subs[sub + i] = acl->ctx_prefix[i - 1];
	sub += strlen(acl->ctx_prefix) + 1;
	oid->subs[sub++] = acl->sec_model;
	oid->subs[sub] = acl->sec_level;
}