#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_74__   TYPE_9__ ;
typedef  struct TYPE_73__   TYPE_8__ ;
typedef  struct TYPE_72__   TYPE_7__ ;
typedef  struct TYPE_71__   TYPE_6__ ;
typedef  struct TYPE_70__   TYPE_5__ ;
typedef  struct TYPE_69__   TYPE_4__ ;
typedef  struct TYPE_68__   TYPE_3__ ;
typedef  struct TYPE_67__   TYPE_2__ ;
typedef  struct TYPE_66__   TYPE_1__ ;
typedef  struct TYPE_65__   TYPE_17__ ;
typedef  struct TYPE_64__   TYPE_16__ ;
typedef  struct TYPE_63__   TYPE_15__ ;
typedef  struct TYPE_62__   TYPE_14__ ;
typedef  struct TYPE_61__   TYPE_13__ ;
typedef  struct TYPE_60__   TYPE_12__ ;
typedef  struct TYPE_59__   TYPE_11__ ;
typedef  struct TYPE_58__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zero ;
typedef  int /*<<< orphan*/  spi_be ;
typedef  int /*<<< orphan*/  dummy_hash_data ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_74__ {scalar_t__ CapsuleMode; int /*<<< orphan*/ * Dh; int /*<<< orphan*/  LifeSeconds; } ;
struct TYPE_73__ {int Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_72__ {int Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_70__ {TYPE_4__* Data; } ;
struct TYPE_71__ {TYPE_5__ Hash; } ;
struct TYPE_69__ {TYPE_9__* Buf; } ;
struct TYPE_68__ {int /*<<< orphan*/  Hash; } ;
struct TYPE_67__ {scalar_t__ Size; } ;
struct TYPE_66__ {int Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_65__ {int Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_64__ {TYPE_7__* MyPublicKey; } ;
struct TYPE_63__ {int /*<<< orphan*/  ServerIP; int /*<<< orphan*/  ClientIP; scalar_t__ SendNatOaRfc; scalar_t__ SendNatOaDraft2; scalar_t__ SendNatOaDraft1; TYPE_1__* SendID2_Buf; int /*<<< orphan*/  SendID2_Port; int /*<<< orphan*/  SendID2_Protocol; int /*<<< orphan*/  SendID2_Type; TYPE_8__* SendID1_Buf; int /*<<< orphan*/  SendID1_Port; int /*<<< orphan*/  SendID1_Protocol; int /*<<< orphan*/  SendID1_Type; scalar_t__ SendID1andID2; int /*<<< orphan*/  CachedTransformSetting; TYPE_12__* CurrentIkeSa; } ;
struct TYPE_62__ {int FlagEncrypted; } ;
struct TYPE_61__ {TYPE_6__ Payload; TYPE_2__* BitArray; } ;
struct TYPE_60__ {int HashSize; int /*<<< orphan*/  SKEYID_a; TYPE_3__ TransformSetting; int /*<<< orphan*/  ResponderCookie; int /*<<< orphan*/  InitiatorCookie; } ;
struct TYPE_59__ {int /*<<< orphan*/  IPsecSaList; } ;
struct TYPE_58__ {int NumResends; TYPE_16__* Dh; struct TYPE_58__* PairIPsecSa; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_9__ IPSEC_SA_TRANSFORM_SETTING ;
typedef  TYPE_10__ IPSECSA ;
typedef  TYPE_11__ IKE_SERVER ;
typedef  TYPE_12__ IKE_SA ;
typedef  TYPE_13__ IKE_PACKET_PAYLOAD ;
typedef  TYPE_14__ IKE_PACKET ;
typedef  int /*<<< orphan*/  IKE_HEADER ;
typedef  int /*<<< orphan*/  IKE_COMMON_HEADER ;
typedef  TYPE_15__ IKE_CLIENT ;
typedef  TYPE_16__ DH_CTX ;
typedef  TYPE_17__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_13__*) ; 
 int /*<<< orphan*/  Copy (TYPE_9__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 scalar_t__ Endian32 (scalar_t__) ; 
 int /*<<< orphan*/  FORCE_LIFETIME_QM ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_17__*) ; 
 scalar_t__ GenerateNewIPsecSaSpi (TYPE_11__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GenerateNewMessageId (TYPE_11__*) ; 
 int /*<<< orphan*/  IKE_EXCHANGE_TYPE_QUICK ; 
 int /*<<< orphan*/  IKE_ID_IPV4_ADDR_SUBNET ; 
 int /*<<< orphan*/  IKE_ID_IPV6_ADDR_SUBNET ; 
 int IKE_MAX_BLOCK_SIZE ; 
 int IKE_MAX_HASH_SIZE ; 
 scalar_t__ IKE_P2_CAPSULE_NAT_TUNNEL_1 ; 
 scalar_t__ IKE_P2_CAPSULE_NAT_TUNNEL_2 ; 
 int /*<<< orphan*/  IKE_PAYLOAD_HASH ; 
 int /*<<< orphan*/  IKE_PAYLOAD_KEY_EXCHANGE ; 
 int /*<<< orphan*/  IKE_PAYLOAD_NAT_OA ; 
 int /*<<< orphan*/  IKE_PAYLOAD_NAT_OA_DRAFT ; 
 int /*<<< orphan*/  IKE_PAYLOAD_NAT_OA_DRAFT_2 ; 
 int /*<<< orphan*/  IKE_PAYLOAD_RAND ; 
 int /*<<< orphan*/  IKE_PROTOCOL_ID_IPSEC_ESP ; 
 int /*<<< orphan*/  IKE_SA_RAND_SIZE ; 
 int /*<<< orphan*/  IPsecLog (TYPE_11__*,int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  IPsecSaSendPacket (TYPE_11__*,TYPE_10__*,TYPE_14__*) ; 
 TYPE_17__* IkeBuild (TYPE_14__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeCalcPhase2InitialIv (int /*<<< orphan*/ *,TYPE_12__*,scalar_t__) ; 
 int /*<<< orphan*/  IkeDebugUdpSendRawPacket (TYPE_14__*) ; 
 TYPE_16__* IkeDhNewCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeFree (TYPE_14__*) ; 
 int /*<<< orphan*/  IkeHMac (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_14__* IkeNew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_13__* IkeNewDataPayload (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_13__* IkeNewIdPayload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_13__* IkeNewNatOaPayload (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_13__* IkeNewProposalPayload (int,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 TYPE_13__* IkeNewSaPayload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_10__*) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ *,int) ; 
 TYPE_17__* MemToBuf (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_17__* NewBuf () ; 
 TYPE_10__* NewIPsecSa (TYPE_11__*,TYPE_15__*,TYPE_12__*,int,scalar_t__,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewListSingle (TYPE_13__*) ; 
 TYPE_17__* RandBuf (int /*<<< orphan*/ ) ; 
 TYPE_13__* TransformSettingToTransformPayloadForIPsec (TYPE_11__*,TYPE_9__*) ; 
 int /*<<< orphan*/  WriteBufBuf (TYPE_17__*,TYPE_17__*) ; 
 int /*<<< orphan*/  WriteBufInt (TYPE_17__*,scalar_t__) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void StartQuickMode(IKE_SERVER *ike, IKE_CLIENT *c)
{
	IPSEC_SA_TRANSFORM_SETTING setting;
	IKE_SA *ike_sa;
	UINT message_id;
	UCHAR iv[IKE_MAX_BLOCK_SIZE];
	// Validate arguments
	if (ike == NULL || c == NULL)
	{
		return;
	}

	if (IsZero(&c->CachedTransformSetting, sizeof(IPSEC_SA_TRANSFORM_SETTING)))
	{
		// Cached transform setting does not exist
		Debug("Error: c->CachedTransformSetting is not existing.\n");
		return;
	}

	ike_sa = c->CurrentIkeSa;
	if (ike_sa == NULL)
	{
		return;
	}

	IPsecLog(ike, NULL, ike_sa, NULL, "LI_START_QM_FROM_SERVER");

	Copy(&setting, &c->CachedTransformSetting, sizeof(IPSEC_SA_TRANSFORM_SETTING));

	message_id = GenerateNewMessageId(ike);

	IkeCalcPhase2InitialIv(iv, ike_sa, message_id);

#ifdef	FORCE_LIFETIME_QM
	setting.LifeSeconds = FORCE_LIFETIME_QM;
#endif	// FORCE_LIFETIME_QM

	if (true)
	{
		IKE_PACKET *ps;
		LIST *payload_list;
		IKE_PACKET_PAYLOAD *send_hash_payload;
		IKE_PACKET_PAYLOAD *send_sa_payload;
		IKE_PACKET_PAYLOAD *send_proposal_payload;
		IKE_PACKET_PAYLOAD *send_transform_payload;
		IKE_PACKET_PAYLOAD *send_rand_payload;
		IKE_PACKET_PAYLOAD *send_key_payload = NULL;
		IKE_PACKET_PAYLOAD *send_id_1 = NULL, *send_id_2 = NULL;
		UINT shared_key_size = 0;
		UCHAR *shared_key = NULL;
		BUF *initiator_rand;
		IPSECSA *ipsec_sa_s_c, *ipsec_sa_c_s;
		BUF *ps_buf;
		UINT after_hash_offset, after_hash_size;
		BUF *ps_buf_after_hash;
		BUF *tmp_buf;
		UINT spi;
		UINT spi_be;
		UCHAR hash1[IKE_MAX_HASH_SIZE];
		DH_CTX *dh = NULL;
		UCHAR dummy_hash_data[IKE_MAX_HASH_SIZE];

		initiator_rand = RandBuf(IKE_SA_RAND_SIZE);

		if (setting.Dh != NULL)
		{
			// Generate DH
			dh = IkeDhNewCtx(setting.Dh);

			if (dh != NULL)
			{
				send_key_payload = IkeNewDataPayload(IKE_PAYLOAD_KEY_EXCHANGE,
					dh->MyPublicKey->Buf, dh->MyPublicKey->Size);
			}
		}

		Zero(dummy_hash_data, sizeof(dummy_hash_data));

		// Dummy hash value
		payload_list = NewListFast(NULL);
		send_hash_payload = IkeNewDataPayload(IKE_PAYLOAD_HASH, dummy_hash_data, ike_sa->HashSize);
		Add(payload_list, send_hash_payload);

		// Determine the SPI
		spi = GenerateNewIPsecSaSpi(ike, 0);
		spi_be = Endian32(spi);

		// SA
		send_transform_payload = TransformSettingToTransformPayloadForIPsec(ike, &setting);
		send_proposal_payload = IkeNewProposalPayload(1, IKE_PROTOCOL_ID_IPSEC_ESP, &spi_be, sizeof(spi_be),
			NewListSingle(send_transform_payload));
		send_sa_payload = IkeNewSaPayload(NewListSingle(send_proposal_payload));
		Add(payload_list, send_sa_payload);

		// Random number
		send_rand_payload = IkeNewDataPayload(IKE_PAYLOAD_RAND, initiator_rand->Buf, initiator_rand->Size);
		Add(payload_list, send_rand_payload);

		// Key exchange
		if (send_key_payload != NULL)
		{
			Add(payload_list, send_key_payload);
		}

		if (c->SendID1andID2)
		{
			// Add the ID payload
			if (setting.CapsuleMode == IKE_P2_CAPSULE_NAT_TUNNEL_1 || setting.CapsuleMode == IKE_P2_CAPSULE_NAT_TUNNEL_2)
			{
				UCHAR zero[32];

				Zero(zero, sizeof(zero));

				// Tunnel Mode
				send_id_1 = IkeNewIdPayload((IsIP4(&c->ServerIP) ? IKE_ID_IPV4_ADDR_SUBNET : IKE_ID_IPV6_ADDR_SUBNET),
					0, 0,
					zero, (IsIP4(&c->ServerIP) ? 8 : 32));

				send_id_2 = IkeNewIdPayload(c->SendID1_Type,
					c->SendID1_Protocol, c->SendID1_Port,
					c->SendID1_Buf->Buf, c->SendID1_Buf->Size);
			}
			else
			{
				// Transport mode
				// Specify in the reverse order in which the client has been specified
				send_id_2 = IkeNewIdPayload(c->SendID1_Type,
					c->SendID1_Protocol, c->SendID1_Port,
					c->SendID1_Buf->Buf, c->SendID1_Buf->Size);

				send_id_1 = IkeNewIdPayload(c->SendID2_Type,
					c->SendID2_Protocol, c->SendID2_Port,
					c->SendID2_Buf->Buf, c->SendID2_Buf->Size);
			}

			Add(payload_list, send_id_1);
			Add(payload_list, send_id_2);
		}

		if (true)
		{
			// NAT-OA payload
			if (c->SendNatOaDraft1)
			{
				Add(payload_list, IkeNewNatOaPayload(IKE_PAYLOAD_NAT_OA_DRAFT, &c->ServerIP));
			}

			if (c->SendNatOaDraft2)
			{
				Add(payload_list, IkeNewNatOaPayload(IKE_PAYLOAD_NAT_OA_DRAFT_2, &c->ServerIP));
			}

			if (c->SendNatOaRfc)
			{
				Add(payload_list, IkeNewNatOaPayload(IKE_PAYLOAD_NAT_OA, &c->ClientIP));
				Add(payload_list, IkeNewNatOaPayload(IKE_PAYLOAD_NAT_OA, &c->ServerIP));
			}
		}

		// Build a packet
		ps = IkeNew(ike_sa->InitiatorCookie, ike_sa->ResponderCookie, IKE_EXCHANGE_TYPE_QUICK,
			false, false, false, message_id, payload_list);

		// Build a temporary packet
		ps_buf = IkeBuild(ps, NULL);

		// Get the payload after the hash part
		after_hash_offset = sizeof(IKE_HEADER) + send_hash_payload->BitArray->Size + sizeof(IKE_COMMON_HEADER);
		after_hash_size = ((ps_buf->Size > after_hash_offset) ? (ps_buf->Size - after_hash_offset) : 0);

		ps_buf_after_hash = MemToBuf(((UCHAR *)ps_buf->Buf) + after_hash_offset, after_hash_size);
		FreeBuf(ps_buf);

		// Calculate the hash #1
		tmp_buf = NewBuf();
		WriteBufInt(tmp_buf, message_id);
		WriteBufBuf(tmp_buf, ps_buf_after_hash);
		IkeHMac(ike_sa->TransformSetting.Hash, hash1, ike_sa->SKEYID_a, ike_sa->HashSize, tmp_buf->Buf, tmp_buf->Size);
		FreeBuf(tmp_buf);

		// Overwrite hash #1
		Copy(send_hash_payload->Payload.Hash.Data->Buf, hash1, ike_sa->HashSize);

		// Create an IPsec SA
		ipsec_sa_c_s = NewIPsecSa(ike, c, ike_sa, true, message_id, false, iv, spi,
			initiator_rand->Buf, initiator_rand->Size, NULL, 0,
			&setting, shared_key, shared_key_size);

		ipsec_sa_s_c = NewIPsecSa(ike, c, ike_sa, true, message_id, true, iv, 0,
			initiator_rand->Buf, initiator_rand->Size, NULL, 0,
			&setting, shared_key, shared_key_size);

		ipsec_sa_c_s->PairIPsecSa = ipsec_sa_s_c;
		ipsec_sa_s_c->PairIPsecSa = ipsec_sa_c_s;

		ipsec_sa_s_c->Dh = dh;

		Insert(ike->IPsecSaList, ipsec_sa_c_s);
		Insert(ike->IPsecSaList, ipsec_sa_s_c);

		// Packet transmission
		ps->FlagEncrypted = true;
		IPsecSaSendPacket(ike, ipsec_sa_s_c, ps);
		ipsec_sa_s_c->NumResends = 3;
#ifdef	RAW_DEBUG
		IkeDebugUdpSendRawPacket(ps);
#endif	// RAW_DEBUG

		IkeFree(ps);
		Free(shared_key);
		FreeBuf(ps_buf_after_hash);
		FreeBuf(initiator_rand);
	}
}