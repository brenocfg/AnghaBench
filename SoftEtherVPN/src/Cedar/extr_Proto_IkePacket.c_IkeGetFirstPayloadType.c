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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  PayloadType; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ IKE_PACKET_PAYLOAD ;

/* Variables and functions */
 int /*<<< orphan*/  IKE_PAYLOAD_NONE ; 
 scalar_t__ LIST_DATA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 

UCHAR IkeGetFirstPayloadType(LIST *o)
{
	IKE_PACKET_PAYLOAD *p;
	// Validate arguments
	if (o == NULL)
	{
		return IKE_PAYLOAD_NONE;
	}

	if (LIST_NUM(o) == 0)
	{
		return IKE_PAYLOAD_NONE;
	}

	p = (IKE_PACKET_PAYLOAD *)LIST_DATA(o, 0);

	return p->PayloadType;
}