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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PKT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAC_PROTO_IPV4 ; 
 int /*<<< orphan*/ * Malloc (scalar_t__) ; 
 int /*<<< orphan*/ * ParsePacket (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WRITE_USHORT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

PKT *ParsePacketIPv4WithDummyMacHeader(UCHAR *buf, UINT size)
{
	UCHAR *tmp;
	UINT tmp_size;
	PKT *ret;
	// Validate arguments
	if (buf == NULL)
	{
		return NULL;
	}

	tmp_size = size + 14;
	tmp = Malloc(tmp_size);
	Zero(tmp, 12);
	WRITE_USHORT(tmp + 12, MAC_PROTO_IPV4);
	Copy(tmp + 14, buf, size);

	ret = ParsePacket(tmp, tmp_size);

	if (ret == NULL)
	{
		Free(tmp);
	}

	return ret;
}