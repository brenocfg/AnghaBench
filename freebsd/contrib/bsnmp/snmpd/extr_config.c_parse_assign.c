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
struct snmp_value {int /*<<< orphan*/  syntax; } ;
struct snmp_node {int /*<<< orphan*/  syntax; } ;
struct asn_oid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRNEXT () ; 
 int /*<<< orphan*/  ERRPOP () ; 
 scalar_t__ ERRPUSH () ; 
#define  SNMP_SYNTAX_COUNTER 139 
#define  SNMP_SYNTAX_COUNTER64 138 
#define  SNMP_SYNTAX_ENDOFMIBVIEW 137 
#define  SNMP_SYNTAX_GAUGE 136 
#define  SNMP_SYNTAX_INTEGER 135 
#define  SNMP_SYNTAX_IPADDRESS 134 
#define  SNMP_SYNTAX_NOSUCHINSTANCE 133 
#define  SNMP_SYNTAX_NOSUCHOBJECT 132 
#define  SNMP_SYNTAX_NULL 131 
#define  SNMP_SYNTAX_OCTETSTRING 130 
#define  SNMP_SYNTAX_OID 129 
#define  SNMP_SYNTAX_TIMETICKS 128 
 char TOK_EOF ; 
 char TOK_EOL ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  gettoken () ; 
 int /*<<< orphan*/  handle_assignment (struct snmp_node const*,struct asn_oid*,struct snmp_value*) ; 
 scalar_t__ ignore ; 
 struct snmp_node* parse_oid (char const*,struct asn_oid*) ; 
 int /*<<< orphan*/  parse_syntax_counter64 (struct snmp_value*) ; 
 int /*<<< orphan*/  parse_syntax_integer (struct snmp_value*) ; 
 int /*<<< orphan*/  parse_syntax_ipaddress (struct snmp_value*) ; 
 int /*<<< orphan*/  parse_syntax_null (struct snmp_value*) ; 
 int /*<<< orphan*/  parse_syntax_octetstring (struct snmp_value*) ; 
 int /*<<< orphan*/  parse_syntax_oid (struct snmp_value*) ; 
 int /*<<< orphan*/  parse_syntax_uint32 (struct snmp_value*) ; 
 int /*<<< orphan*/  report (char*,...) ; 
 int /*<<< orphan*/  snmp_value_free (struct snmp_value*) ; 
 char token ; 

__attribute__((used)) static void
parse_assign(const char *varname)
{
	struct snmp_value value;
	struct asn_oid vindex;
	const struct snmp_node *node;

	node = parse_oid(varname, &vindex);
	if (token != '=')
		report("'=' expected, got '%c'", token);
	gettoken();

	if (ignore) {
		/* skip rest of line */
		while (token != TOK_EOL && token != TOK_EOF)
			gettoken();
		return;
	}
	if (node == NULL)
		report("unknown variable");

	switch (value.syntax = node->syntax) {

	  case SNMP_SYNTAX_NULL:
		parse_syntax_null(&value);
		break;

	  case SNMP_SYNTAX_INTEGER:
		parse_syntax_integer(&value);
		break;

	  case SNMP_SYNTAX_COUNTER64:
		parse_syntax_counter64(&value);
		break;

	  case SNMP_SYNTAX_OCTETSTRING:
		parse_syntax_octetstring(&value);
		break;

	  case SNMP_SYNTAX_OID:
		parse_syntax_oid(&value);
		break;

	  case SNMP_SYNTAX_IPADDRESS:
		parse_syntax_ipaddress(&value);
		break;

	  case SNMP_SYNTAX_COUNTER:
	  case SNMP_SYNTAX_GAUGE:
	  case SNMP_SYNTAX_TIMETICKS:
		parse_syntax_uint32(&value);
		break;

	  case SNMP_SYNTAX_NOSUCHOBJECT:
	  case SNMP_SYNTAX_NOSUCHINSTANCE:
	  case SNMP_SYNTAX_ENDOFMIBVIEW:
		abort();
	}

	if (ERRPUSH()) {
		snmp_value_free(&value);
		ERRNEXT();
	}

	handle_assignment(node, &vindex, &value);

	ERRPOP();
}