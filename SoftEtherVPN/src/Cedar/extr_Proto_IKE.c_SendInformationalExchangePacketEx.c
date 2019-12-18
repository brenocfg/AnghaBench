#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_9__ ;
typedef  struct TYPE_46__   TYPE_8__ ;
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_12__ ;
typedef  struct TYPE_37__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dummy_hash_data ;
typedef  int /*<<< orphan*/  cp ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_44__ {int /*<<< orphan*/  Iv; int /*<<< orphan*/  Key; } ;
typedef  TYPE_6__ UCHAR ;
struct TYPE_47__ {int FlagEncrypted; int /*<<< orphan*/  MessageId; } ;
struct TYPE_42__ {TYPE_3__* Data; } ;
struct TYPE_43__ {TYPE_4__ Hash; } ;
struct TYPE_46__ {TYPE_5__ Payload; TYPE_1__* BitArray; } ;
struct TYPE_40__ {int /*<<< orphan*/  Hash; } ;
struct TYPE_45__ {scalar_t__ InitiatorCookie; scalar_t__ ResponderCookie; int /*<<< orphan*/  CryptoKey; int /*<<< orphan*/  HashSize; int /*<<< orphan*/  SKEYID_a; TYPE_2__ TransformSetting; } ;
struct TYPE_41__ {int /*<<< orphan*/  Buf; } ;
struct TYPE_39__ {scalar_t__ Size; } ;
struct TYPE_38__ {scalar_t__ Size; scalar_t__ Buf; } ;
struct TYPE_37__ {int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIP; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIP; TYPE_7__* CurrentIkeSa; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_7__ IKE_SA ;
typedef  TYPE_8__ IKE_PACKET_PAYLOAD ;
typedef  TYPE_9__ IKE_PACKET ;
typedef  int /*<<< orphan*/  IKE_HEADER ;
typedef  TYPE_6__ IKE_CRYPTO_PARAM ;
typedef  int /*<<< orphan*/  IKE_COMMON_HEADER ;
typedef  TYPE_11__ IKE_CLIENT ;
typedef  TYPE_12__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_12__*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_12__*) ; 
 int /*<<< orphan*/  GenerateNewMessageId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IKE_EXCHANGE_TYPE_INFORMATION ; 
 int IKE_MAX_HASH_SIZE ; 
 int /*<<< orphan*/  IKE_PAYLOAD_HASH ; 
 int /*<<< orphan*/  IKE_UDP_TYPE_ISAKMP ; 
 TYPE_12__* IkeBuild (TYPE_9__*,TYPE_6__*) ; 
 int /*<<< orphan*/  IkeCalcPhase2InitialIv (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IkeDebugUdpSendRawPacket (TYPE_9__*) ; 
 int /*<<< orphan*/  IkeFree (TYPE_9__*) ; 
 int /*<<< orphan*/  IkeFreePayload (TYPE_8__*) ; 
 int /*<<< orphan*/  IkeHMac (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_9__* IkeNew (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_8__* IkeNewDataPayload (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IkeSendUdpPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_12__* MemToBuf (TYPE_6__*,scalar_t__) ; 
 TYPE_12__* NewBuf () ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 scalar_t__ Rand64 () ; 
 int /*<<< orphan*/  WriteBufBuf (TYPE_12__*,TYPE_12__*) ; 
 int /*<<< orphan*/  WriteBufInt (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_6__*,int) ; 

void SendInformationalExchangePacketEx(IKE_SERVER *ike, IKE_CLIENT *c, IKE_PACKET_PAYLOAD *payload, bool force_plain, UINT64 init_cookie, UINT64 resp_cookie)
{
	IKE_SA *sa;
	IKE_PACKET *ps;
	LIST *payload_list;
	UCHAR dummy_hash_data[IKE_MAX_HASH_SIZE];
	IKE_PACKET_PAYLOAD *hash_payload;
	BUF *ps_buf;
	UINT after_hash_offset, after_hash_size;
	BUF *ps_buf_after_hash;
	BUF *tmp_buf;
	UCHAR hash[IKE_MAX_HASH_SIZE];
	IKE_CRYPTO_PARAM cp;
	bool plain = false;
	// Validate arguments
	if (ike == NULL || c == NULL || payload == NULL)
	{
		IkeFreePayload(payload);
		return;
	}

	sa = c->CurrentIkeSa;
	if (sa == NULL)
	{
		plain = true;
	}

	if (force_plain)
	{
		plain = true;
	}

	if (plain && (init_cookie == 0 && resp_cookie == 0))
	{
		init_cookie = Rand64();
		resp_cookie = 0;
	}

	payload_list = NewListFast(NULL);

	Zero(dummy_hash_data, sizeof(dummy_hash_data));

	// Hash payload
	if (plain == false)
	{
		hash_payload = IkeNewDataPayload(IKE_PAYLOAD_HASH, dummy_hash_data, sa->HashSize);
		Add(payload_list, hash_payload);
	}

	// Body
	Add(payload_list, payload);

	// Packet creation
	ps = IkeNew((plain ? init_cookie : sa->InitiatorCookie), (plain ? resp_cookie : sa->ResponderCookie),
		IKE_EXCHANGE_TYPE_INFORMATION, false, false, false,
		GenerateNewMessageId(ike), payload_list);

	if (plain == false)
	{
		// Build a temporary packet
		ps_buf = IkeBuild(ps, NULL);

		// Get the payload after the hash part
		after_hash_offset = sizeof(IKE_HEADER) + hash_payload->BitArray->Size + sizeof(IKE_COMMON_HEADER);
		after_hash_size = ((ps_buf->Size > after_hash_offset) ? (ps_buf->Size - after_hash_offset) : 0);

		ps_buf_after_hash = MemToBuf(((UCHAR *)ps_buf->Buf) + after_hash_offset, after_hash_size);
		FreeBuf(ps_buf);

		// Calculate the hash
		tmp_buf = NewBuf();
		WriteBufInt(tmp_buf, ps->MessageId);
		WriteBufBuf(tmp_buf, ps_buf_after_hash);
		IkeHMac(sa->TransformSetting.Hash, hash, sa->SKEYID_a, sa->HashSize, tmp_buf->Buf, tmp_buf->Size);
		FreeBuf(tmp_buf);

		// Overwrite the hash
		Copy(hash_payload->Payload.Hash.Data->Buf, hash, sa->HashSize);

		ps->FlagEncrypted = true;
		FreeBuf(ps_buf_after_hash);
	}

	// Packet reply
	Zero(&cp, sizeof(cp));

	if (plain == false)
	{
		cp.Key = sa->CryptoKey;
		IkeCalcPhase2InitialIv(cp.Iv, sa, ps->MessageId);
	}

	ps_buf = IkeBuild(ps, &cp);

	IkeSendUdpPacket(ike, IKE_UDP_TYPE_ISAKMP, &c->ServerIP, c->ServerPort,
		&c->ClientIP, c->ClientPort,
		ps_buf->Buf, ps_buf->Size);

#ifdef	RAW_DEBUG
	IkeDebugUdpSendRawPacket(ps);
#endif	// RAW_DEBUG

	Free(ps_buf);

	IkeFree(ps);
}