#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_5__ {scalar_t__ Protocol; int IsControl; int DataSize; int /*<<< orphan*/ * Lcp; int /*<<< orphan*/  Data; } ;
typedef  TYPE_1__ PPP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (int*,int) ; 
 int /*<<< orphan*/  FreePPPPacket (TYPE_1__*) ; 
 scalar_t__ PPP_PROTOCOL_CHAP ; 
 scalar_t__ PPP_PROTOCOL_IPCP ; 
 scalar_t__ PPP_PROTOCOL_LCP ; 
 scalar_t__ PPP_PROTOCOL_PAP ; 
 int /*<<< orphan*/ * ParseLCP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ READ_USHORT (int*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

PPP_PACKET *ParsePPPPacket(void *data, UINT size)
{
	PPP_PACKET *pp;
	UCHAR *buf;
	// Validate arguments
	if (data == NULL || size == 0)
	{
		return NULL;
	}

	pp = ZeroMalloc(sizeof(PPP_PACKET));

	buf = (UCHAR *)data;

	if (buf[0] != 0xff)
	{
		goto LABEL_ERROR;
	}
	size--;
	buf++;

	// Control
	if (size < 1)
	{
		goto LABEL_ERROR;
	}
	if (buf[0] != 0x03)
	{
		goto LABEL_ERROR;
	}
	size--;
	buf++;

	// Protocol
	if (size < 2)
	{
		goto LABEL_ERROR;
	}
	pp->Protocol = READ_USHORT(buf);
	size -= 2;
	buf += 2;

	if (pp->Protocol == PPP_PROTOCOL_LCP || pp->Protocol == PPP_PROTOCOL_PAP || pp->Protocol == PPP_PROTOCOL_CHAP || pp->Protocol == PPP_PROTOCOL_IPCP)
	{
		pp->IsControl = true;
	}

	pp->Data = Clone(buf, size);
	pp->DataSize = size;

	if (pp->IsControl)
	{
		pp->Lcp = ParseLCP(pp->Protocol, pp->Data, pp->DataSize);
		if (pp->Lcp == NULL)
		{
			goto LABEL_ERROR;
		}
	}

	return pp;

LABEL_ERROR:
	FreePPPPacket(pp);
	return NULL;
}