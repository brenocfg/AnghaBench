#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bulk_send_key ;
typedef  int /*<<< orphan*/  bulk_recv_key ;
typedef  int UINT64 ;
typedef  void* UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_9__ {int NextSendSeqNo; int ServerMode; int Magic_Disconnect; int NextKeepAliveInterval; int Dns_TranId; int BulkNextSeqNo; int /*<<< orphan*/ * BulkNextIv; void* BulkRecvKey; void* BulkSendKey; void* SendFifo; void* RecvFifo; int /*<<< orphan*/  ReplyAckList; int /*<<< orphan*/ * NextIv; int /*<<< orphan*/ * Key_Recv; int /*<<< orphan*/ * Key_Send; int /*<<< orphan*/ * Key_Init; int /*<<< orphan*/ * Magic_KeepAliveResponse; int /*<<< orphan*/ * Magic_KeepAliveRequest; void* RecvSegmentList; void* SendSegmentList; void* LatestRecvMyTick; void* LastRecvTick; scalar_t__ LastSentTick; void* YourPort; int /*<<< orphan*/  YourIp; void* MyPort; int /*<<< orphan*/  MyIp; } ;
typedef  TYPE_1__ RUDP_SESSION ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 TYPE_2__* NewBuf () ; 
 void* NewFifo () ; 
 int /*<<< orphan*/  NewInt64List (int) ; 
 void* NewList (int /*<<< orphan*/ ) ; 
 void* NewSharedBuffer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RUDPCompareSegmentList ; 
 int RUDP_KEEPALIVE_INTERVAL_MAX ; 
 int RUDP_KEEPALIVE_INTERVAL_MIN ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ *,int) ; 
 int Rand16 () ; 
 int Rand32 () ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* Tick64 () ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteBufStr (TYPE_2__*,char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

RUDP_SESSION *RUDPNewSession(bool server_mode, IP *my_ip, UINT my_port, IP *your_ip, UINT your_port, UCHAR *init_key)
{
	RUDP_SESSION *se;
	UCHAR key1[SHA1_SIZE];
	UCHAR key2[SHA1_SIZE];
	UCHAR bulk_send_key[SHA1_SIZE];
	UCHAR bulk_recv_key[SHA1_SIZE];
	BUF *b;

	se = ZeroMalloc(sizeof(RUDP_SESSION));

	Copy(&se->MyIp, my_ip, sizeof(IP));
	se->MyPort = my_port;

	Copy(&se->YourIp, your_ip, sizeof(IP));
	se->YourPort = your_port;

	Copy(se->Key_Init, init_key, SHA1_SIZE);
	se->LastSentTick = 0;
	se->LastRecvTick = Tick64();
	se->LatestRecvMyTick = Tick64();

	se->NextSendSeqNo = 1;

	se->ServerMode = server_mode;

	se->SendSegmentList = NewList(RUDPCompareSegmentList);
	se->RecvSegmentList = NewList(RUDPCompareSegmentList);

	// Generate the two keys
	b = NewBuf();
	WriteBuf(b, init_key, SHA1_SIZE);
	WriteBufStr(b, "zurukko");
	Sha1(key1, b->Buf, b->Size);
	FreeBuf(b);

	b = NewBuf();
	WriteBuf(b, init_key, SHA1_SIZE);
	WriteBuf(b, key1, SHA1_SIZE);
	WriteBufStr(b, "yasushineko");
	Sha1(key2, b->Buf, b->Size);
	FreeBuf(b);

	// Generate the magic number for the KeepAlive
	b = NewBuf();
	WriteBuf(b, init_key, SHA1_SIZE);
	WriteBufStr(b, "Magic_KeepAliveRequest");
	Sha1(se->Magic_KeepAliveRequest, b->Buf, b->Size);
	FreeBuf(b);
	b = NewBuf();
	WriteBuf(b, init_key, SHA1_SIZE);
	WriteBufStr(b, "Magic_KeepAliveResponse");
	Sha1(se->Magic_KeepAliveResponse, b->Buf, b->Size);
	FreeBuf(b);

	if (server_mode == false)
	{
		se->Magic_Disconnect = 0xffffffff00000000ULL | (UINT64)(Rand32());
	}

	Copy(se->Key_Init, init_key, SHA1_SIZE);

	if (se->ServerMode)
	{
		Copy(se->Key_Send, key1, SHA1_SIZE);
		Copy(se->Key_Recv, key2, SHA1_SIZE);
	}
	else
	{
		Copy(se->Key_Send, key2, SHA1_SIZE);
		Copy(se->Key_Recv, key1, SHA1_SIZE);
	}

	Rand(se->NextIv, sizeof(se->NextIv));

	se->ReplyAckList = NewInt64List(true);

	se->NextKeepAliveInterval = RUDP_KEEPALIVE_INTERVAL_MIN + (Rand32() % (RUDP_KEEPALIVE_INTERVAL_MAX - RUDP_KEEPALIVE_INTERVAL_MIN));

	se->RecvFifo = NewFifo();
	se->SendFifo = NewFifo();

	se->Dns_TranId = Rand16() % 65535 + 1;

	// Generate the bulk transfer key
	Rand(bulk_send_key, sizeof(bulk_send_key));
	Rand(bulk_recv_key, sizeof(bulk_recv_key));

	se->BulkSendKey = NewSharedBuffer(bulk_send_key, sizeof(bulk_send_key));
	se->BulkRecvKey = NewSharedBuffer(bulk_recv_key, sizeof(bulk_recv_key));

	Rand(se->BulkNextIv, sizeof(se->BulkNextIv));
	se->BulkNextSeqNo = 1;

	return se;
}