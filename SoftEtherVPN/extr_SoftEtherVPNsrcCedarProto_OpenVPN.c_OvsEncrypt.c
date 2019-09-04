#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {int IsAeadCipher; int IvSize; } ;
struct TYPE_8__ {int Size; } ;
typedef  TYPE_1__ MD ;
typedef  TYPE_2__ CIPHER ;

/* Variables and functions */
 scalar_t__ CipherProcess (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ CipherProcessAead (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 scalar_t__ MdProcess (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

UINT OvsEncrypt(CIPHER *cipher, MD *md, UCHAR *iv, UCHAR *tag, UCHAR *dest, UCHAR *src, UINT src_size, UCHAR *aad, UINT aad_size)
{
	// Validate arguments
	if (cipher == NULL || (cipher->IsAeadCipher == false && md == NULL))
	{
		return 0;
	}

	if (cipher->IsAeadCipher)
	{
		// Encrypt in AEAD mode (no HMAC)
		UINT dest_size = CipherProcessAead(cipher, iv, tag, 16, dest, src, src_size, aad, aad_size);
		if (dest_size == 0)
		{
			Debug("OvsEncrypt(): CipherProcessAead() failed!\n");
			return 0;
		}

		return dest_size;
	}
	else
	{
		// Encrypt in non-AEAD mode (with HMAC)
		UINT ret;
		UINT dest_size = CipherProcess(cipher, iv, dest + md->Size + cipher->IvSize, src, src_size);
		if (dest_size == 0)
		{
			Debug("OvsEncrypt(): CipherProcess() failed!\n");
			return 0;
		}

		// Copy the IV
		Copy(dest + md->Size, iv, cipher->IvSize);
		dest_size += cipher->IvSize;

		// Calculate the HMAC
		ret = MdProcess(md, dest, dest + md->Size, dest_size);
		if (ret == 0)
		{
			Debug("OvsEncrypt(): MdProcess() failed!\n");
			return 0;
		}

		return dest_size + ret;
	}
}