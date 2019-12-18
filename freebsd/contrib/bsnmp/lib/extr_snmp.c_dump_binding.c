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
typedef  size_t u_int ;
struct TYPE_3__ {int len; int* octets; } ;
struct TYPE_4__ {int integer; int uint32; int counter64; int /*<<< orphan*/ * ipaddress; int /*<<< orphan*/  oid; TYPE_1__ octetstring; } ;
struct snmp_value {int syntax; TYPE_2__ v; int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int ASN_OIDSTRLEN ; 
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
 int asn_oid2str_r (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snmp_printf (char*,...) ; 

__attribute__((used)) static void
dump_binding(const struct snmp_value *b)
{
	u_int i;
	char buf[ASN_OIDSTRLEN];

	snmp_printf("%s=", asn_oid2str_r(&b->var, buf));
	switch (b->syntax) {

	  case SNMP_SYNTAX_NULL:
		snmp_printf("NULL");
		break;

	  case SNMP_SYNTAX_INTEGER:
		snmp_printf("INTEGER %d", b->v.integer);
		break;

	  case SNMP_SYNTAX_OCTETSTRING:
		snmp_printf("OCTET STRING %lu:", b->v.octetstring.len);
		for (i = 0; i < b->v.octetstring.len; i++)
			snmp_printf(" %02x", b->v.octetstring.octets[i]);
		break;

	  case SNMP_SYNTAX_OID:
		snmp_printf("OID %s", asn_oid2str_r(&b->v.oid, buf));
		break;

	  case SNMP_SYNTAX_IPADDRESS:
		snmp_printf("IPADDRESS %u.%u.%u.%u", b->v.ipaddress[0],
		    b->v.ipaddress[1], b->v.ipaddress[2], b->v.ipaddress[3]);
		break;

	  case SNMP_SYNTAX_COUNTER:
		snmp_printf("COUNTER %u", b->v.uint32);
		break;

	  case SNMP_SYNTAX_GAUGE:
		snmp_printf("GAUGE %u", b->v.uint32);
		break;

	  case SNMP_SYNTAX_TIMETICKS:
		snmp_printf("TIMETICKS %u", b->v.uint32);
		break;

	  case SNMP_SYNTAX_COUNTER64:
		snmp_printf("COUNTER64 %lld", b->v.counter64);
		break;

	  case SNMP_SYNTAX_NOSUCHOBJECT:
		snmp_printf("NoSuchObject");
		break;

	  case SNMP_SYNTAX_NOSUCHINSTANCE:
		snmp_printf("NoSuchInstance");
		break;

	  case SNMP_SYNTAX_ENDOFMIBVIEW:
		snmp_printf("EndOfMibView");
		break;

	  default:
		snmp_printf("UNKNOWN SYNTAX %u", b->syntax);
		break;
	}
}