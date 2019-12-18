#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_9__ ;
typedef  struct TYPE_56__   TYPE_8__ ;
typedef  struct TYPE_55__   TYPE_7__ ;
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_15__ ;
typedef  struct TYPE_47__   TYPE_14__ ;
typedef  struct TYPE_46__   TYPE_13__ ;
typedef  struct TYPE_45__   TYPE_12__ ;
typedef  struct TYPE_44__   TYPE_11__ ;
typedef  struct TYPE_43__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cp ;
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
struct TYPE_55__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Data; int /*<<< orphan*/  DestPort; int /*<<< orphan*/  DstIP; int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  SrcIP; } ;
typedef  TYPE_7__ UDPPACKET ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_51__ {int /*<<< orphan*/  Hash; } ;
struct TYPE_57__ {TYPE_14__* IkeClient; int /*<<< orphan*/  LastCommTick; int /*<<< orphan*/  HashSize; int /*<<< orphan*/  SKEYID_a; TYPE_3__ TransformSetting; int /*<<< orphan*/  CryptoKey; scalar_t__ Established; } ;
struct TYPE_56__ {int /*<<< orphan*/  Now; } ;
struct TYPE_54__ {int Size; scalar_t__ Buf; } ;
struct TYPE_53__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_44__ {scalar_t__ MessageType; TYPE_6__* Spi; TYPE_5__* MessageData; } ;
struct TYPE_52__ {TYPE_11__ Notice; int /*<<< orphan*/  Delete; } ;
struct TYPE_50__ {int Size; scalar_t__ Buf; } ;
struct TYPE_49__ {int Size; } ;
struct TYPE_48__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_47__ {TYPE_9__* CurrentIkeSa; int /*<<< orphan*/  LastCommTick; } ;
struct TYPE_46__ {int /*<<< orphan*/  Iv; int /*<<< orphan*/  Key; } ;
struct TYPE_45__ {scalar_t__ InitiatorCookie; scalar_t__ ResponderCookie; scalar_t__ MessageId; int FlagEncrypted; int /*<<< orphan*/  PayloadList; TYPE_2__* DecryptedPayload; } ;
struct TYPE_43__ {TYPE_4__ Payload; TYPE_1__* BitArray; } ;
typedef  TYPE_8__ IKE_SERVER ;
typedef  TYPE_9__ IKE_SA ;
typedef  TYPE_10__ IKE_PACKET_PAYLOAD ;
typedef  TYPE_11__ IKE_PACKET_NOTICE_PAYLOAD ;
typedef  int /*<<< orphan*/  IKE_PACKET_DELETE_PAYLOAD ;
typedef  TYPE_12__ IKE_PACKET ;
typedef  TYPE_13__ IKE_CRYPTO_PARAM ;
typedef  int /*<<< orphan*/  IKE_COMMON_HEADER ;
typedef  TYPE_14__ IKE_CLIENT ;
typedef  TYPE_15__ BUF ;

/* Variables and functions */
 TYPE_9__* FindIkeSaByResponderCookieAndClient (TYPE_8__*,scalar_t__,TYPE_14__*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_15__*) ; 
 int IKE_MAX_HASH_SIZE ; 
 scalar_t__ IKE_NOTICE_DPD_REQUEST ; 
 scalar_t__ IKE_NOTICE_DPD_RESPONSE ; 
 int /*<<< orphan*/  IKE_PAYLOAD_DELETE ; 
 int /*<<< orphan*/  IKE_PAYLOAD_HASH ; 
 int /*<<< orphan*/  IKE_PAYLOAD_NOTICE ; 
 int /*<<< orphan*/  IkeCalcPhase2InitialIv (int /*<<< orphan*/ ,TYPE_9__*,scalar_t__) ; 
 scalar_t__ IkeCompareHash (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IkeDebugUdpSendRawPacket (TYPE_12__*) ; 
 int /*<<< orphan*/  IkeFree (TYPE_12__*) ; 
 TYPE_10__* IkeGetPayload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int IkeGetPayloadNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IkeHMac (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IkeNewNoticeDpdPayload (int,scalar_t__,scalar_t__,int) ; 
 TYPE_12__* IkeParse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_13__*) ; 
 TYPE_15__* NewBuf () ; 
 int /*<<< orphan*/  ProcDeletePayload (TYPE_8__*,TYPE_14__*,int /*<<< orphan*/ *) ; 
 int READ_UINT (int /*<<< orphan*/ ) ; 
 scalar_t__ READ_UINT64 (int /*<<< orphan*/ *) ; 
 TYPE_9__* SearchIkeSaByCookie (TYPE_8__*,scalar_t__,scalar_t__) ; 
 TYPE_14__* SearchOrCreateNewIkeClientForIkePacket (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_12__*) ; 
 int /*<<< orphan*/  SendInformationalExchangePacket (TYPE_8__*,TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_15__*,void*,int) ; 
 int /*<<< orphan*/  WriteBufInt (TYPE_15__*,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_13__*,int) ; 

void ProcIkeInformationalExchangePacketRecv(IKE_SERVER *ike, UDPPACKET *p, IKE_PACKET *header)
{
	IKE_CLIENT *c;
	IKE_SA *ike_sa;
	// Validate arguments
	if (ike == NULL || p == NULL || header == NULL || header->InitiatorCookie == 0 || header->ResponderCookie == 0
		|| header->MessageId == 0 || header->FlagEncrypted == false)
	{
		return;
	}

	c = SearchOrCreateNewIkeClientForIkePacket(ike, &p->SrcIP, p->SrcPort, &p->DstIP, p->DestPort, header);

	if (c == NULL)
	{
		return;
	}

	ike_sa = FindIkeSaByResponderCookieAndClient(ike, header->ResponderCookie, c);

	if (ike_sa != NULL && ike_sa->Established)
	{
		IKE_PACKET *pr;
		IKE_CRYPTO_PARAM cp;

		// Packet decoding
		Zero(&cp, sizeof(cp));
		cp.Key = ike_sa->CryptoKey;
		IkeCalcPhase2InitialIv(cp.Iv, ike_sa, header->MessageId);

		pr = IkeParse(p->Data, p->Size, &cp);
#ifdef	RAW_DEBUG
		IkeDebugUdpSendRawPacket(pr);
#endif	// RAW_DEBUG
		if (pr != NULL)
		{
			// Get the hash payload
			IKE_PACKET_PAYLOAD *hash_payload;

			hash_payload = IkeGetPayload(pr->PayloadList, IKE_PAYLOAD_HASH, 0);
			if (hash_payload != NULL)
			{
				// Get the payload after the hash
				UINT header_and_hash_size = sizeof(IKE_COMMON_HEADER) + hash_payload->BitArray->Size;
				void *after_hash_data = ((UCHAR *)pr->DecryptedPayload->Buf) + header_and_hash_size;
				if (pr->DecryptedPayload->Size > header_and_hash_size)
				{
					UINT after_hash_size = pr->DecryptedPayload->Size - header_and_hash_size;
					UCHAR hash1[IKE_MAX_HASH_SIZE];
					BUF *hash1_buf;

					hash1_buf = NewBuf();
					WriteBufInt(hash1_buf, header->MessageId);
					WriteBuf(hash1_buf, after_hash_data, after_hash_size);

					IkeHMac(ike_sa->TransformSetting.Hash, hash1, ike_sa->SKEYID_a, ike_sa->HashSize,
						hash1_buf->Buf, hash1_buf->Size);

					// Compare the hash value
					if (IkeCompareHash(hash_payload, hash1, ike_sa->HashSize))
					{
						UINT i, num;
						// Handle the deletion payload
						num = IkeGetPayloadNum(pr->PayloadList, IKE_PAYLOAD_DELETE);
						for (i = 0;i < num;i++)
						{
							IKE_PACKET_PAYLOAD *payload = IkeGetPayload(pr->PayloadList, IKE_PAYLOAD_DELETE, i);
							IKE_PACKET_DELETE_PAYLOAD *del = &payload->Payload.Delete;

							ProcDeletePayload(ike, c, del);
						}
						num = IkeGetPayloadNum(pr->PayloadList, IKE_PAYLOAD_NOTICE);
						// Handle the notification payload
						for (i = 0;i < num;i++)
						{
							IKE_PACKET_PAYLOAD *payload = IkeGetPayload(pr->PayloadList, IKE_PAYLOAD_NOTICE, i);
							IKE_PACKET_NOTICE_PAYLOAD *n = &payload->Payload.Notice;

							if (n->MessageType == IKE_NOTICE_DPD_REQUEST || n->MessageType == IKE_NOTICE_DPD_RESPONSE)
							{
								if (n->MessageData != NULL && n->MessageData->Size == sizeof(UINT))
								{
									UINT seq_no = READ_UINT(n->MessageData->Buf);

									if (n->Spi->Size == (sizeof(UINT64) * 2))
									{
										UINT64 init_cookie = READ_UINT64(((UCHAR *)n->Spi->Buf));
										UINT64 resp_cookie = READ_UINT64(((UCHAR *)n->Spi->Buf) + sizeof(UINT64));

										if (init_cookie != 0 && resp_cookie != 0)
										{
											IKE_SA *found_ike_sa = SearchIkeSaByCookie(ike, init_cookie, resp_cookie);

											if (found_ike_sa != NULL && found_ike_sa->IkeClient == c)
											{
												if (n->MessageType == IKE_NOTICE_DPD_REQUEST)
												{
													// Return the DPD Response (ACK) for the DPD Request
													SendInformationalExchangePacket(ike, c,
														IkeNewNoticeDpdPayload(true, init_cookie, resp_cookie,
														seq_no));
												}

												// Update the status of the IKE SA
												found_ike_sa->LastCommTick = ike->Now;
												ike_sa->LastCommTick = ike->Now;
												found_ike_sa->IkeClient->LastCommTick = ike->Now;
												ike_sa->IkeClient->LastCommTick = ike->Now;
												ike_sa->IkeClient->CurrentIkeSa = ike_sa;
											}
										}
									}
								}
							}
						}
					}

					FreeBuf(hash1_buf);
				}
			}

			IkeFree(pr);
		}
	}
}