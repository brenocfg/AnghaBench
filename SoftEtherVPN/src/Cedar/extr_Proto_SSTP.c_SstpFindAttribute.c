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
typedef  scalar_t__ UCHAR ;
struct TYPE_7__ {scalar_t__ AttributeId; } ;
struct TYPE_6__ {int /*<<< orphan*/  AttributeList; } ;
typedef  TYPE_1__ SSTP_PACKET ;
typedef  TYPE_2__ SSTP_ATTRIBUTE ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

SSTP_ATTRIBUTE *SstpFindAttribute(SSTP_PACKET *p, UCHAR attribute_id)
{
	UINT i;
	// Validate arguments
	if (p == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(p->AttributeList);i++)
	{
		SSTP_ATTRIBUTE *a = LIST_DATA(p->AttributeList, i);

		if (a->AttributeId == attribute_id)
		{
			return a;
		}
	}

	return NULL;
}