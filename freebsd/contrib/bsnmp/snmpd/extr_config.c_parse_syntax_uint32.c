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
struct TYPE_2__ {int uint32; } ;
struct snmp_value {TYPE_1__ v; } ;

/* Variables and functions */
 scalar_t__ TOK_NUM ; 
 int /*<<< orphan*/  gettoken () ; 
 int numval ; 
 int /*<<< orphan*/  report (char*) ; 
 scalar_t__ token ; 

__attribute__((used)) static void
parse_syntax_uint32(struct snmp_value *value)
{

	if (token != TOK_NUM)
		report("bad number syntax");
	if (numval > 0xffffffff)
		report("number too large");
	value->v.uint32 = numval;
	gettoken();
}