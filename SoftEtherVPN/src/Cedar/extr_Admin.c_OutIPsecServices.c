#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  L2TP_DefaultHub; int /*<<< orphan*/  IPsec_Secret; int /*<<< orphan*/  EtherIP_IPsec; int /*<<< orphan*/  L2TP_IPsec; int /*<<< orphan*/  L2TP_Raw; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ IPSEC_SERVICES ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutIPsecServices(PACK *p, IPSEC_SERVICES *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddBool(p, "L2TP_Raw", t->L2TP_Raw);
	PackAddBool(p, "L2TP_IPsec", t->L2TP_IPsec);
	PackAddBool(p, "EtherIP_IPsec", t->EtherIP_IPsec);

	PackAddStr(p, "IPsec_Secret", t->IPsec_Secret);
	PackAddStr(p, "L2TP_DefaultHub", t->L2TP_DefaultHub);
}