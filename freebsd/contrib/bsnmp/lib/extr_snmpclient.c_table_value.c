#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u_int ;
typedef  char u_char ;
struct asn_oid {int dummy; } ;
struct TYPE_8__ {int len; int /*<<< orphan*/  octets; } ;
struct TYPE_10__ {size_t counter64; int /*<<< orphan*/  uint32; int /*<<< orphan*/  ipaddress; struct asn_oid oid; TYPE_3__ octetstring; int /*<<< orphan*/  integer; } ;
struct TYPE_6__ {scalar_t__* subs; } ;
struct snmp_value {scalar_t__ syntax; TYPE_5__ v; TYPE_1__ var; } ;
struct TYPE_7__ {int len; } ;
struct snmp_table {size_t index_size; TYPE_4__* entries; TYPE_2__ table; } ;
struct entry {size_t found; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_9__ {scalar_t__ syntax; scalar_t__ subid; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  abort () ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seterr (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  snmp_client ; 

__attribute__((used)) static int
table_value(const struct snmp_table *descr, struct entry *e,
    const struct snmp_value *b)
{
	u_int i;
	u_char *ptr;

	for (i = descr->index_size;
	    descr->entries[i].syntax != SNMP_SYNTAX_NULL; i++)
		if (descr->entries[i].subid ==
		    b->var.subs[descr->table.len + 1])
			break;
	if (descr->entries[i].syntax == SNMP_SYNTAX_NULL)
		return (0);

	/* check syntax */
	if (b->syntax != descr->entries[i].syntax) {
		seterr(&snmp_client, "bad syntax (%u instead of %u)", b->syntax,
		    descr->entries[i].syntax);
		return (-1);
	}

	switch (b->syntax) {

	  case SNMP_SYNTAX_INTEGER:
		*(int32_t *)(void *)((u_char *)e + descr->entries[i].offset) =
		    b->v.integer;
		break;

	  case SNMP_SYNTAX_OCTETSTRING:
		if ((ptr = malloc(b->v.octetstring.len + 1)) == NULL) {
			seterr(&snmp_client, "no memory for string");
			return (-1);
		}
		memcpy(ptr, b->v.octetstring.octets, b->v.octetstring.len);
		ptr[b->v.octetstring.len] = '\0';
		*(u_char **)(void *)((u_char *)e + descr->entries[i].offset) =
		    ptr;
		*(size_t *)(void *)((u_char *)e + descr->entries[i].offset +
		    sizeof(u_char *)) = b->v.octetstring.len;
		break;

	  case SNMP_SYNTAX_OID:
		*(struct asn_oid *)(void *)((u_char *)e + descr->entries[i].offset) =
		    b->v.oid;
		break;

	  case SNMP_SYNTAX_IPADDRESS:
		memcpy((u_char *)e + descr->entries[i].offset,
		    b->v.ipaddress, 4);
		break;

	  case SNMP_SYNTAX_COUNTER:
	  case SNMP_SYNTAX_GAUGE:
	  case SNMP_SYNTAX_TIMETICKS:
		*(uint32_t *)(void *)((u_char *)e + descr->entries[i].offset) =
		    b->v.uint32;
		break;

	  case SNMP_SYNTAX_COUNTER64:
		*(uint64_t *)(void *)((u_char *)e + descr->entries[i].offset) =
		    b->v.counter64;
		break;

	  case SNMP_SYNTAX_NULL:
	  case SNMP_SYNTAX_NOSUCHOBJECT:
	  case SNMP_SYNTAX_NOSUCHINSTANCE:
	  case SNMP_SYNTAX_ENDOFMIBVIEW:
		abort();
	}
	e->found |= (uint64_t)1 << i;

	return (0);
}