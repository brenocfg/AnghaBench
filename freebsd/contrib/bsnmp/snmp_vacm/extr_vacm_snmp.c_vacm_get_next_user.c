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
typedef  scalar_t__ uint ;
struct vacm_user {scalar_t__ sec_model; int /*<<< orphan*/  secname; } ;
struct asn_oid {scalar_t__ len; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int SNMP_ADM_STR32_SIZ ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 struct vacm_user* vacm_first_user () ; 
 struct vacm_user* vacm_next_user (struct vacm_user*) ; 
 scalar_t__ vacm_user_index_decode (struct asn_oid const*,scalar_t__,scalar_t__*,char*) ; 

__attribute__((used)) static struct vacm_user *
vacm_get_next_user(const struct asn_oid *oid, uint sub)
{
	int32_t smodel;
	char uname[SNMP_ADM_STR32_SIZ];
	struct vacm_user *user;

	if (oid->len - sub == 0)
		return (vacm_first_user());

	if (vacm_user_index_decode(oid, sub, &smodel, uname) < 0)
		return (NULL);

	for (user = vacm_first_user(); user != NULL; user = vacm_next_user(user))
		if (strcmp(uname, user->secname) == 0 &&
		    user->sec_model == smodel)
			return (vacm_next_user(user));

	return (NULL);
}