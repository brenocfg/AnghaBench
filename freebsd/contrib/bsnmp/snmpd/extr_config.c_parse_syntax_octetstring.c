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
typedef  scalar_t__ u_long ;
typedef  int u_char ;
struct TYPE_3__ {scalar_t__ len; int* octets; } ;
struct TYPE_4__ {TYPE_1__ octetstring; } ;
struct snmp_value {TYPE_2__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRNEXT () ; 
 int /*<<< orphan*/  ERRPOP () ; 
 scalar_t__ ERRPUSH () ; 
 scalar_t__ TOK_NUM ; 
 scalar_t__ TOK_STR ; 
 int /*<<< orphan*/  free (int*) ; 
 char gettoken () ; 
 int* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int numval ; 
 int* realloc (int*,scalar_t__) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  strval ; 
 scalar_t__ strvallen ; 
 scalar_t__ token ; 

__attribute__((used)) static void
parse_syntax_octetstring(struct snmp_value *value)
{
	u_long alloc;
	u_char *noct;

	if (token == TOK_STR) {
		value->v.octetstring.len = strvallen;
		value->v.octetstring.octets = malloc(strvallen);
		(void)memcpy(value->v.octetstring.octets, strval, strvallen);
		gettoken();
		return;
	}

	/* XX:XX:XX syntax */
	value->v.octetstring.octets = NULL;
	value->v.octetstring.len = 0;

	if (token != TOK_NUM)
		/* empty string is allowed */
		return;

	if (ERRPUSH()) {
		free(value->v.octetstring.octets);
		ERRNEXT();
	}

	alloc = 0;
	for (;;) {
		if (token != TOK_NUM)
			report("bad OCTETSTRING syntax");
		if (numval > 0xff)
			report("byte value too large");
		if (alloc == value->v.octetstring.len) {
			alloc += 100;
			noct = realloc(value->v.octetstring.octets, alloc);
			if (noct == NULL)
				report("%m");
			value->v.octetstring.octets = noct;
		}
		value->v.octetstring.octets[value->v.octetstring.len++]
		    = numval;
		if (gettoken() != ':')
			break;
		gettoken();
	}
	ERRPOP();
}