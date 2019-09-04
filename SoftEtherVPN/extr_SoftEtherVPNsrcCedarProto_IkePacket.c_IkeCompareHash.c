#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {TYPE_1__* Data; } ;
struct TYPE_7__ {TYPE_3__ Hash; } ;
struct TYPE_9__ {scalar_t__ PayloadType; TYPE_2__ Payload; } ;
struct TYPE_6__ {scalar_t__ Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_4__ IKE_PACKET_PAYLOAD ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 scalar_t__ IKE_PAYLOAD_HASH ; 

bool IkeCompareHash(IKE_PACKET_PAYLOAD *hash_payload, void *hash_data, UINT hash_size)
{
	//char tmp1[MAX_SIZE], tmp2[MAX_SIZE];
	// Validate arguments
	if (hash_payload == NULL || hash_data == NULL || hash_size == 0)
	{
		return false;
	}

	if (hash_payload->PayloadType != IKE_PAYLOAD_HASH)
	{
		return false;
	}

	if (hash_payload->Payload.Hash.Data == NULL)
	{
		return false;
	}

	if (hash_payload->Payload.Hash.Data->Size != hash_size)
	{
		return false;
	}

	//BinToStrEx(tmp1, sizeof(tmp1), hash_payload->Payload.Hash.Data->Buf, hash_size);
	//BinToStrEx(tmp2, sizeof(tmp2), hash_data, hash_size);

	//Debug("IkeCompareHash\n  1: %s\n  2: %s\n", tmp1, tmp2);

	if (Cmp(hash_payload->Payload.Hash.Data->Buf, hash_data, hash_size) != 0)
	{
		return false;
	}

	return true;
}