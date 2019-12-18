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
struct transport {int /*<<< orphan*/  or_index; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int SNMP_ERR_INCONS_VALUE ; 
 int SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct transport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  or_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_list ; 

int
trans_unregister(struct transport *t)
{
	if (!TAILQ_EMPTY(&t->table))
		return (SNMP_ERR_INCONS_VALUE);

	or_unregister(t->or_index);
	TAILQ_REMOVE(&transport_list, t, link);

	return (SNMP_ERR_NOERROR);
}