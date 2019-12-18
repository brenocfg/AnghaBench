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
typedef  size_t u_int ;
struct snmp_pdu {scalar_t__ version; scalar_t__ error_status; scalar_t__ nbindings; TYPE_1__* bindings; } ;
struct TYPE_2__ {scalar_t__ syntax; int /*<<< orphan*/  var; } ;

/* Variables and functions */
 scalar_t__ SNMP_ERR_NOERROR ; 
 scalar_t__ SNMP_ERR_NOSUCHNAME ; 
 scalar_t__ SNMP_SYNTAX_ENDOFMIBVIEW ; 
 scalar_t__ SNMP_V1 ; 
 int /*<<< orphan*/  asn_is_suboid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
ok_getnext(const struct snmp_pdu * req, const struct snmp_pdu * resp)
{
	u_int i;

	if (resp->version != req->version) {
		warnx("SNMP GETNEXT: response has wrong version");
		return (-1);
	}

	if (resp->error_status == SNMP_ERR_NOSUCHNAME)
		return (0);

	if (resp->error_status != SNMP_ERR_NOERROR) {
		warnx("SNMP GETNEXT: error %d", resp->error_status);
		return (-1);
	}
	if (resp->nbindings != req->nbindings) {
		warnx("SNMP GETNEXT: bad number of bindings in response");
		return (-1);
	}
	for (i = 0; i < req->nbindings; i++) {
		if (!asn_is_suboid(&req->bindings[i].var,
		    &resp->bindings[i].var)) {
			if (i != 0)
				warnx("SNMP GETNEXT: inconsistent table "
				    "response");
			return (0);
		}
		if (resp->version != SNMP_V1 &&
		    resp->bindings[i].syntax == SNMP_SYNTAX_ENDOFMIBVIEW)
			return (0);

		if (resp->bindings[i].syntax != req->bindings[i].syntax) {
			warnx("SNMP GETNEXT: bad syntax in response");
			return (0);
		}
	}
	return (1);
}