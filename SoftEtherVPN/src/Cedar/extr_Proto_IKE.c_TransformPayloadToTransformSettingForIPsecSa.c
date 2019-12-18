#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_17__ {int /*<<< orphan*/  TransformId; } ;
struct TYPE_16__ {int /*<<< orphan*/  Engine; TYPE_1__* IPsec; } ;
struct TYPE_15__ {int CryptoKeySize; int OnlyCapsuleModeIsInvalid; scalar_t__ CapsuleMode; TYPE_11__* Crypto; int /*<<< orphan*/ * Hash; void* DhId; int /*<<< orphan*/  Dh; void* HashId; int /*<<< orphan*/  CryptoId; void* LifeKilobytes; void* LifeSeconds; } ;
struct TYPE_14__ {int /*<<< orphan*/  UdpListener; } ;
struct TYPE_13__ {int* KeySizes; scalar_t__ VariableKeySize; } ;
typedef  TYPE_2__ IPSEC_SA_TRANSFORM_SETTING ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_3__ IKE_SERVER ;
typedef  TYPE_4__ IKE_PACKET_TRANSFORM_PAYLOAD ;

/* Variables and functions */
 TYPE_11__* GetIkeCrypto (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetIkeDh (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/ * GetIkeHash (int /*<<< orphan*/ ,int,void*) ; 
 scalar_t__ IKE_P2_CAPSULE_NAT_TRANSPORT_1 ; 
 scalar_t__ IKE_P2_CAPSULE_NAT_TRANSPORT_2 ; 
 scalar_t__ IKE_P2_CAPSULE_NAT_TUNNEL_1 ; 
 scalar_t__ IKE_P2_CAPSULE_NAT_TUNNEL_2 ; 
 scalar_t__ IKE_P2_CAPSULE_TRANSPORT ; 
 scalar_t__ IKE_P2_CAPSULE_TUNNEL ; 
#define  IKE_P2_LIFE_TYPE_KILOBYTES 129 
#define  IKE_P2_LIFE_TYPE_SECONDS 128 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_CAPSULE ; 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_DH_GROUP ; 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_HMAC ; 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_KEY_SIZE ; 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_LIFE_TYPE ; 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_LIFE_VALUE ; 
 void* INFINITE ; 
 int /*<<< orphan*/  IPSEC_PORT_IPSEC_ESP_RAW ; 
 int IkeCheckKeySize (TYPE_11__*,int) ; 
 void* IkeGetTransformValue (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IkeGetTransformValueNum (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int IsUdpPortOpened (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool TransformPayloadToTransformSettingForIPsecSa(IKE_SERVER *ike, IKE_PACKET_TRANSFORM_PAYLOAD *transform, IPSEC_SA_TRANSFORM_SETTING *setting, IP *server_ip)
{
	UINT i;
	UINT capsule_mode;
	bool is_esp_supported;
	// Validate arguments
	if (ike == NULL || transform == NULL || setting == NULL || server_ip == NULL)
	{
		return false;
	}

	is_esp_supported = IsUdpPortOpened(ike->IPsec->UdpListener, server_ip, IPSEC_PORT_IPSEC_ESP_RAW);

	Zero(setting, sizeof(IPSEC_SA_TRANSFORM_SETTING));

	setting->CryptoId = transform->TransformId;
	setting->HashId = IkeGetTransformValue(transform, IKE_TRANSFORM_VALUE_P2_HMAC, 0);

	setting->DhId = IkeGetTransformValue(transform, IKE_TRANSFORM_VALUE_P2_DH_GROUP, 0);

	setting->LifeKilobytes = INFINITE;
	setting->LifeSeconds = INFINITE;

	for (i = 0;i < IkeGetTransformValueNum(transform, IKE_TRANSFORM_VALUE_P2_LIFE_TYPE);i++)
	{
		UINT life_type = IkeGetTransformValue(transform, IKE_TRANSFORM_VALUE_P2_LIFE_TYPE, i);

		switch (life_type)
		{
		case IKE_P2_LIFE_TYPE_SECONDS:		// Number of seconds
			setting->LifeSeconds = IkeGetTransformValue(transform, IKE_TRANSFORM_VALUE_P2_LIFE_VALUE, i);
			break;

		case IKE_P2_LIFE_TYPE_KILOBYTES:	// Kilobytes
			setting->LifeKilobytes = IkeGetTransformValue(transform, IKE_TRANSFORM_VALUE_P2_LIFE_VALUE, i);
			break;

		default:
			// Unsupported expiration type
			return false;
		}
	}

	setting->Crypto = GetIkeCrypto(ike->Engine, true, setting->CryptoId);
	setting->Hash = GetIkeHash(ike->Engine, true, setting->HashId);
	setting->Dh = GetIkeDh(ike->Engine, true, setting->DhId);

	if (setting->Crypto == NULL || setting->Hash == NULL)
	{
		// Unsupported algorithm
		return false;
	}

	if (setting->Crypto->VariableKeySize)
	{
		// Get the actual key size in the case of variable key size
		setting->CryptoKeySize = IkeGetTransformValue(transform, IKE_TRANSFORM_VALUE_P2_KEY_SIZE, 0);

		// bits -> bytes
		setting->CryptoKeySize = setting->CryptoKeySize / 8;

		if (setting->CryptoKeySize == 0 || IkeCheckKeySize(setting->Crypto, setting->CryptoKeySize) == false)
		{
			// The key size is not specified or inappropriate
			return false;
		}
	}
	else
	{
		// Get a fixed key length for fixed key size
		setting->CryptoKeySize = setting->Crypto->KeySizes[0];
	}

	capsule_mode = IkeGetTransformValue(transform, IKE_TRANSFORM_VALUE_P2_CAPSULE, 0);
	if (capsule_mode != IKE_P2_CAPSULE_NAT_TUNNEL_1 && capsule_mode != IKE_P2_CAPSULE_NAT_TUNNEL_2 &&
		capsule_mode != IKE_P2_CAPSULE_NAT_TRANSPORT_1 && capsule_mode != IKE_P2_CAPSULE_NAT_TRANSPORT_2)
	{
		// No support for UDP encapsulation mode except for the NAT-Traversal
		if (capsule_mode == IKE_P2_CAPSULE_TRANSPORT || capsule_mode == IKE_P2_CAPSULE_TUNNEL)
		{
			if (is_esp_supported == false)
			{
				setting->OnlyCapsuleModeIsInvalid = true;
				return false;
			}
			else
			{
				// It is an environment that can send and receive ESP packets
			}
		}
		else
		{
			return false;
		}
	}

	setting->CapsuleMode = capsule_mode;

	return true;
}