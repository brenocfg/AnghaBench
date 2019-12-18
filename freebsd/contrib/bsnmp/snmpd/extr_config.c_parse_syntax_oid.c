#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ len; scalar_t__* subs; } ;
struct TYPE_4__ {TYPE_1__ oid; } ;
struct snmp_value {TYPE_2__ v; } ;

/* Variables and functions */
 scalar_t__ ASN_MAXID ; 
 scalar_t__ ASN_MAXOIDLEN ; 
 scalar_t__ TOK_NUM ; 
 char gettoken () ; 
 scalar_t__ numval ; 
 int /*<<< orphan*/  report (char*) ; 
 scalar_t__ token ; 

__attribute__((used)) static void
parse_syntax_oid(struct snmp_value *value)
{
	value->v.oid.len = 0;

	if (token != TOK_NUM)
		return;

	for (;;) {
		if (token != TOK_NUM)
			report("bad OID syntax");
		if (numval > ASN_MAXID)
			report("subid too large");
		if (value->v.oid.len == ASN_MAXOIDLEN)
			report("OID too long");
		value->v.oid.subs[value->v.oid.len++] = numval;
		if (gettoken() != '.')
			break;
		gettoken();
	}
}