#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {scalar_t__ Type; scalar_t__ VendorID; } ;
struct TYPE_6__ {int /*<<< orphan*/  AvpList; } ;
typedef  TYPE_1__ L2TP_PACKET ;
typedef  TYPE_2__ L2TP_AVP ;

/* Variables and functions */
 scalar_t__ L2TPV3_CISCO_AVP_SESSION_ID_LOCAL ; 
 scalar_t__ L2TPV3_CISCO_AVP_SESSION_ID_REMOTE ; 
 scalar_t__ L2TPV3_CISCO_AVP_TUNNEL_ID ; 
 scalar_t__ L2TP_AVP_TYPE_V3_SESSION_ID_LOCAL ; 
 scalar_t__ L2TP_AVP_TYPE_V3_SESSION_ID_REMOTE ; 
 scalar_t__ L2TP_AVP_TYPE_V3_TUNNEL_ID ; 
 scalar_t__ L2TP_AVP_VENDOR_ID_CISCO ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

L2TP_AVP *GetAVPValueEx(L2TP_PACKET *p, UINT type, UINT vendor_id)
{
	UINT i;
	// Validate arguments
	if (p == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(p->AvpList);i++)
	{
		L2TP_AVP *a = LIST_DATA(p->AvpList, i);

		if (a->Type == type && a->VendorID == vendor_id)
		{
			return a;
		}
	}

	if (vendor_id == 0)
	{
		if (type == L2TP_AVP_TYPE_V3_TUNNEL_ID)
		{
			return GetAVPValueEx(p, L2TPV3_CISCO_AVP_TUNNEL_ID, L2TP_AVP_VENDOR_ID_CISCO);
		}
		else if (type == L2TP_AVP_TYPE_V3_SESSION_ID_LOCAL)
		{
			return GetAVPValueEx(p, L2TPV3_CISCO_AVP_SESSION_ID_LOCAL, L2TP_AVP_VENDOR_ID_CISCO);
		}
		else if (type == L2TP_AVP_TYPE_V3_SESSION_ID_REMOTE)
		{
			return GetAVPValueEx(p, L2TPV3_CISCO_AVP_SESSION_ID_REMOTE, L2TP_AVP_VENDOR_ID_CISCO);
		}
	}

	return NULL;
}