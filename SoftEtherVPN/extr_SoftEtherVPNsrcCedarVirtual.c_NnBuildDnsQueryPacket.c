#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  header ;
typedef  int USHORT ;
struct TYPE_4__ {int Flag1; int Flag2; void* NumQuery; void* TransactionId; } ;
typedef  TYPE_1__ DNSV4_HEADER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  BuildDnsQueryPacket (int /*<<< orphan*/ *,char*,int) ; 
 void* Endian16 (int) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  SeekBufToBegin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

BUF *NnBuildDnsQueryPacket(char *hostname, USHORT tran_id)
{
	BUF *buf = NewBuf();
	DNSV4_HEADER header;

	Zero(&header, sizeof(header));

	header.TransactionId = Endian16(tran_id);
	header.Flag1 = 0x01;
	header.Flag2 = 0x00;
	header.NumQuery = Endian16(1);

	WriteBuf(buf, &header, sizeof(header));

	BuildDnsQueryPacket(buf, hostname, false);

	SeekBufToBegin(buf);

	return buf;
}