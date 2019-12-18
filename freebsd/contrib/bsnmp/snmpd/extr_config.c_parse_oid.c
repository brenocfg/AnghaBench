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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ u_int ;
typedef  scalar_t__ u_char ;
typedef  struct snmp_node {int /*<<< orphan*/  name; } const snmp_node ;
struct asn_oid {scalar_t__ len; scalar_t__* subs; } ;

/* Variables and functions */
 scalar_t__ ASN_MAXID ; 
 scalar_t__ ASN_MAXOIDLEN ; 
 char TOK_HOST ; 
 char TOK_NUM ; 
 char TOK_STR ; 
 int /*<<< orphan*/  asn_append_oid (struct asn_oid*,struct asn_oid*) ; 
 int /*<<< orphan*/  gethost (scalar_t__*,scalar_t__*) ; 
 char gettoken () ; 
 scalar_t__ numval ; 
 int /*<<< orphan*/  report (char*,...) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__* strval ; 
 scalar_t__ strvallen ; 
 char token ; 
 struct snmp_node const* tree ; 
 size_t tree_size ; 

__attribute__((used)) static const struct snmp_node *
parse_oid(const char *varname, struct asn_oid *oid)
{
	struct snmp_node *node;
	u_int i;
	u_char ip[4];
	struct asn_oid str_oid;

	for (node = tree; node < &tree[tree_size]; node++)
		if (strcmp(varname, node->name) == 0)
			break;
	if (node == &tree[tree_size])
		node = NULL;

	oid->len = 0;
	while (token == '.') {
		if (gettoken() == TOK_NUM) {
			if (numval > ASN_MAXID)
				report("subid too large %#jx",
				    (uintmax_t)numval);
			if (oid->len == ASN_MAXOIDLEN)
				report("index too long");
			if (gettoken() != ':')
				oid->subs[oid->len++] = numval;
			else {
				str_oid.len = 0;
				str_oid.subs[str_oid.len++] = numval;
				while (gettoken() == TOK_NUM) {
					str_oid.subs[str_oid.len++] = numval;
					if (gettoken() != ':')
						break;
				}
				oid->subs[oid->len++] = str_oid.len;
				asn_append_oid(oid, &str_oid);
			}

		} else if (token == TOK_STR) {
			if (strvallen + oid->len + 1 > ASN_MAXOIDLEN)
				report("oid too long");
			oid->subs[oid->len++] = strvallen;
			for (i = 0; i < strvallen; i++)
				oid->subs[oid->len++] = strval[i];
			gettoken();

		} else if (token == TOK_HOST) {
			gethost(strval, ip);
			if (oid->len + 4 > ASN_MAXOIDLEN)
				report("index too long");
			for (i = 0; i < 4; i++)
				oid->subs[oid->len++] = ip[i];
			gettoken();
		} else
			report("bad token in index");
	}

	return (node);
}