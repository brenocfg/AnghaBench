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
struct target_notify {int /*<<< orphan*/  name; } ;
struct asn_oid {scalar_t__ len; } ;

/* Variables and functions */
 int SNMP_ADM_STR32_SIZ ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ target_decode_index (struct asn_oid const*,scalar_t__,char*) ; 
 struct target_notify* target_first_notify () ; 
 struct target_notify* target_next_notify (struct target_notify*) ; 

__attribute__((used)) static struct target_notify *
target_get_next_notify(const struct asn_oid *oid, uint sub)
{
	char nname[SNMP_ADM_STR32_SIZ];
	struct target_notify *notify;

	if (oid->len - sub == 0)
		return (target_first_notify());

	if (target_decode_index(oid, sub, nname) < 0)
		return (NULL);

	for (notify = target_first_notify(); notify != NULL;
	    notify = target_next_notify(notify))
		if (strcmp(nname, notify->name) == 0)
			return (target_next_notify(notify));

	return (NULL);
}