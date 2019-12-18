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
struct snmp_client {scalar_t__ next_reqid; scalar_t__ max_reqid; scalar_t__ min_reqid; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */

__attribute__((used)) static int32_t
snmp_next_reqid(struct snmp_client * c)
{
	int32_t i;

	i = c->next_reqid;
	if (c->next_reqid >= c->max_reqid)
		c->next_reqid = c->min_reqid;
	else
		c->next_reqid++;
	return (i);
}