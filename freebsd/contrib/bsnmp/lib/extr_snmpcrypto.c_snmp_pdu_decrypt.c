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
struct TYPE_2__ {scalar_t__ priv_proto; } ;
struct snmp_pdu {TYPE_1__ user; } ;
typedef  enum snmp_code { ____Placeholder_snmp_code } snmp_code ;

/* Variables and functions */
 int SNMP_CODE_BADSECLEVEL ; 
 int SNMP_CODE_OK ; 
 scalar_t__ SNMP_PRIV_NOPRIV ; 

enum snmp_code
snmp_pdu_decrypt(const struct snmp_pdu *pdu)
{
	if (pdu->user.priv_proto != SNMP_PRIV_NOPRIV)
		return (SNMP_CODE_BADSECLEVEL);

	return (SNMP_CODE_OK);
}