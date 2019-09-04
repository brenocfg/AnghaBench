#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {int Size; int /*<<< orphan*/  NextHeader; } ;
typedef  TYPE_1__ IPV6_OPTION_HEADER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void BuildAndAddIPv6PacketOptionHeader(BUF *b, IPV6_OPTION_HEADER *opt, UCHAR next_header, UINT size)
{
	IPV6_OPTION_HEADER *h;
	UINT total_size;
	// Validate arguments
	if (b == NULL || opt == NULL)
	{
		return;
	}

	total_size = size;
	if ((total_size % 8) != 0)
	{
		total_size = ((total_size / 8) + 1) * 8;
	}

	h = ZeroMalloc(total_size);
	Copy(h, opt, size);
	h->Size = (total_size / 8) - 1;
	h->NextHeader = next_header;

	WriteBuf(b, h, total_size);

	Free(h);
}