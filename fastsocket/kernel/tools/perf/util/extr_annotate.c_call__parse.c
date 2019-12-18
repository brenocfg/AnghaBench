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
struct TYPE_2__ {void* addr; int /*<<< orphan*/ * name; } ;
struct ins_operands {char* raw; TYPE_1__ target; } ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 void* strtoull (char*,char**,int) ; 

__attribute__((used)) static int call__parse(struct ins_operands *ops)
{
	char *endptr, *tok, *name;

	ops->target.addr = strtoull(ops->raw, &endptr, 16);

	name = strchr(endptr, '<');
	if (name == NULL)
		goto indirect_call;

	name++;

	tok = strchr(name, '>');
	if (tok == NULL)
		return -1;

	*tok = '\0';
	ops->target.name = strdup(name);
	*tok = '>';

	return ops->target.name == NULL ? -1 : 0;

indirect_call:
	tok = strchr(endptr, '(');
	if (tok != NULL) {
		ops->target.addr = 0;
		return 0;
	}

	tok = strchr(endptr, '*');
	if (tok == NULL)
		return -1;

	ops->target.addr = strtoull(tok + 1, NULL, 16);
	return 0;
}