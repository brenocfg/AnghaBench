#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  size_t UINT ;
typedef  size_t UCHAR ;
struct TYPE_5__ {int SubnetMaskLen; int /*<<< orphan*/  Gateway; int /*<<< orphan*/  Network; scalar_t__ Exists; } ;
struct TYPE_4__ {scalar_t__ NumExistingRoutes; TYPE_2__* Entries; } ;
typedef  TYPE_1__ DHCP_CLASSLESS_ROUTE_TABLE ;
typedef  TYPE_2__ DHCP_CLASSLESS_ROUTE ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (size_t*,int /*<<< orphan*/ *,size_t) ; 
 size_t IPToUINT (int /*<<< orphan*/ *) ; 
 size_t MAX_DHCP_CLASSLESS_ROUTE_ENTRIES ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  SeekBufToBegin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,size_t*,int) ; 
 int /*<<< orphan*/  Zero (size_t*,int) ; 

BUF *DhcpBuildClasslessRouteData(DHCP_CLASSLESS_ROUTE_TABLE *t)
{
	BUF *b;
	UINT i;
	// Validate arguments
	if (t == NULL || t->NumExistingRoutes == 0)
	{
		return NULL;
	}

	b = NewBuf();

	for (i = 0;i < MAX_DHCP_CLASSLESS_ROUTE_ENTRIES;i++)
	{
		DHCP_CLASSLESS_ROUTE *r = &t->Entries[i];

		if (r->Exists && r->SubnetMaskLen <= 32)
		{
			UCHAR c;
			UINT data_len;
			UINT ip32;
			UCHAR tmp[4];

			// Width of subnet mask
			c = (UCHAR)r->SubnetMaskLen;
			WriteBuf(b, &c, 1);

			// Number of significant octets
			data_len = (r->SubnetMaskLen + 7) / 8;
			Zero(tmp, sizeof(tmp));
			Copy(tmp, &r->Network, data_len);
			WriteBuf(b, tmp, data_len);

			// Gateway
			ip32 = IPToUINT(&r->Gateway);
			WriteBuf(b, &ip32, sizeof(UINT));
		}
	}

	SeekBufToBegin(b);

	return b;
}