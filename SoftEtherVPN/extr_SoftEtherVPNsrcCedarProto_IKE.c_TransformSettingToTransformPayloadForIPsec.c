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
struct TYPE_5__ {int HashId; int DhId; scalar_t__ LifeSeconds; scalar_t__ LifeKilobytes; int CryptoKeySize; int CapsuleMode; int /*<<< orphan*/  CryptoId; TYPE_1__* Crypto; int /*<<< orphan*/ * Dh; } ;
struct TYPE_4__ {scalar_t__ VariableKeySize; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ IPSEC_SA_TRANSFORM_SETTING ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  int /*<<< orphan*/  IKE_PACKET_PAYLOAD ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IKE_P2_LIFE_TYPE_KILOBYTES ; 
 int IKE_P2_LIFE_TYPE_SECONDS ; 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_CAPSULE ; 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_DH_GROUP ; 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_HMAC ; 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_KEY_SIZE ; 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_LIFE_TYPE ; 
 int /*<<< orphan*/  IKE_TRANSFORM_VALUE_P2_LIFE_VALUE ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/ * IkeNewTransformPayload (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeNewTransformValue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 

IKE_PACKET_PAYLOAD *TransformSettingToTransformPayloadForIPsec(IKE_SERVER *ike, IPSEC_SA_TRANSFORM_SETTING *setting)
{
	LIST *value_list;
	// Validate arguments
	if (ike == NULL || setting == NULL)
	{
		return NULL;
	}

	value_list = NewListFast(NULL);

	Add(value_list, IkeNewTransformValue(IKE_TRANSFORM_VALUE_P2_HMAC, setting->HashId));

	if (setting->Dh != NULL)
	{
		Add(value_list, IkeNewTransformValue(IKE_TRANSFORM_VALUE_P2_DH_GROUP, setting->DhId));
	}

	if (setting->LifeSeconds != INFINITE)
	{
		Add(value_list, IkeNewTransformValue(IKE_TRANSFORM_VALUE_P2_LIFE_TYPE, IKE_P2_LIFE_TYPE_SECONDS));
		Add(value_list, IkeNewTransformValue(IKE_TRANSFORM_VALUE_P2_LIFE_VALUE, setting->LifeSeconds));
	}

	if (setting->LifeKilobytes != INFINITE)
	{
		Add(value_list, IkeNewTransformValue(IKE_TRANSFORM_VALUE_P2_LIFE_TYPE, IKE_P2_LIFE_TYPE_KILOBYTES));
		Add(value_list, IkeNewTransformValue(IKE_TRANSFORM_VALUE_P2_LIFE_VALUE, setting->LifeKilobytes));
	}

	if (setting->Crypto->VariableKeySize)
	{
		Add(value_list, IkeNewTransformValue(IKE_TRANSFORM_VALUE_P2_KEY_SIZE, setting->CryptoKeySize * 8));
	}

	Add(value_list, IkeNewTransformValue(IKE_TRANSFORM_VALUE_P2_CAPSULE, setting->CapsuleMode));

	return IkeNewTransformPayload(1, setting->CryptoId, value_list);
}