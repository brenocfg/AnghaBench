#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int SessionCreated; int LoginFlag; void* Error; int /*<<< orphan*/  SessionId; TYPE_1__* Api; } ;
struct TYPE_9__ {scalar_t__ Type; int /*<<< orphan*/  Object; scalar_t__ Private; } ;
struct TYPE_8__ {scalar_t__ (* C_SignInit ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ;scalar_t__ (* C_Sign ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*,scalar_t__*) ;} ;
typedef  TYPE_2__ SEC_OBJ ;
typedef  TYPE_3__ SECURE ;
typedef  TYPE_4__ CK_MECHANISM ;

/* Variables and functions */
 int /*<<< orphan*/  CKM_RSA_PKCS ; 
 scalar_t__ CKR_OK ; 
 int /*<<< orphan*/  Debug (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  HashForSign (int /*<<< orphan*/ *,int,void*,scalar_t__) ; 
 void* SEC_ERROR_BAD_PARAMETER ; 
 void* SEC_ERROR_HARDWARE_ERROR ; 
 void* SEC_ERROR_NOT_LOGIN ; 
 void* SEC_ERROR_NO_SESSION ; 
 scalar_t__ SEC_K ; 
 int SIGN_HASH_SIZE ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*,scalar_t__*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*,scalar_t__*) ; 

bool SignSecByObject(SECURE *sec, SEC_OBJ *obj, void *dst, void *src, UINT size)
{
	CK_MECHANISM mechanism = {CKM_RSA_PKCS, NULL, 0};
	UINT ret;
	UCHAR hash[SIGN_HASH_SIZE];
	// Validate arguments
	if (sec == NULL)
	{
		return false;
	}
	if (obj == NULL || dst == NULL || src == NULL)
	{
		sec->Error = SEC_ERROR_BAD_PARAMETER;
		return false;
	}
	if (sec->SessionCreated == false)
	{
		sec->Error = SEC_ERROR_NO_SESSION;
		return false;
	}
	if (sec->LoginFlag == false && obj->Private)
	{
		sec->Error = SEC_ERROR_NOT_LOGIN;
		return false;
	}
	if (obj->Type != SEC_K)
	{
		sec->Error = SEC_ERROR_BAD_PARAMETER;
		return false;
	}

	// Hash
	HashForSign(hash, sizeof(hash), src, size);

	// Signature initialization
	ret = sec->Api->C_SignInit(sec->SessionId, &mechanism, obj->Object);
	if (ret != CKR_OK)
	{
		// Failure
		sec->Error = SEC_ERROR_HARDWARE_ERROR;
		Debug("C_SignInit Error: 0x%x\n", ret);
		return false;
	}

	// Perform Signing
	size = 128;
	// First try with 1024 bit
	ret = sec->Api->C_Sign(sec->SessionId, hash, sizeof(hash), dst, &size);
	if (ret != CKR_OK && 128 < size && size <= 4096/8)
	{
		// Retry with expanded bits
		ret = sec->Api->C_Sign(sec->SessionId, hash, sizeof(hash), dst, &size);
	}
	if (ret != CKR_OK || size == 0 || size > 4096/8)
	{
		// Failure
		sec->Error = SEC_ERROR_HARDWARE_ERROR;
		Debug("C_Sign Error: 0x%x  size:%d\n", ret, size);
		return false;
	}

	return true;
}