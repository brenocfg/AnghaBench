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
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {int BlockSize; int IvSize; scalar_t__ IsAeadCipher; } ;
struct TYPE_8__ {int Size; } ;
typedef  TYPE_1__ MD ;
typedef  TYPE_2__ CIPHER ;

/* Variables and functions */
 int CipherProcess (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int CipherProcessAead (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 scalar_t__ MdProcess (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int OPENVPN_TAG_SIZE ; 

UINT OvsDecrypt(CIPHER *cipher, MD *md, UCHAR *iv, UCHAR *dest, UCHAR *src, UINT size)
{
	// Validate arguments
	if (cipher == NULL)
	{
		return 0;
	}

	if (cipher->IsAeadCipher)
	{
		UCHAR *tag = src;

		if (iv == NULL || size <= OPENVPN_TAG_SIZE)
		{
			return 0;
		}

		src += OPENVPN_TAG_SIZE;
		size -= OPENVPN_TAG_SIZE;

		// Payload
		if (size >= 1 && (cipher->BlockSize == 0 || (size % cipher->BlockSize) == 0))
		{
			// Decryption
			UINT ret = CipherProcessAead(cipher, iv, tag, OPENVPN_TAG_SIZE, dest, src, size, iv, sizeof(UINT));
			if (ret == 0)
			{
				Debug("OvsDecrypt(): CipherProcessAead() failed!\n");
			}

			return ret;
		}
	}
	else
	{
		UCHAR *hmac;
		UCHAR hmac_test[128];

		if (md == NULL || iv == NULL || size < (md->Size + cipher->IvSize + sizeof(UINT)))
		{
			return 0;
		}

		// HMAC
		hmac = src;
		src += md->Size;
		size -= md->Size;

		if (MdProcess(md, hmac_test, src, size) == 0)
		{
			Debug("OvsDecrypt(): MdProcess() failed!\n");
			return 0;
		}

		if (Cmp(hmac_test, hmac, md->Size) != 0)
		{
			Debug("OvsDecrypt(): HMAC verification failed!\n");
			return 0;
		}

		// IV
		Copy(iv, src, cipher->IvSize);
		src += cipher->IvSize;
		size -= cipher->IvSize;

		// Payload
		if (size >= 1 && (cipher->BlockSize == 0 || (size % cipher->BlockSize) == 0))
		{
			// Decryption
			UINT ret = CipherProcess(cipher, iv, dest, src, size);
			if (ret == 0)
			{
				Debug("OvsDecrypt(): CipherProcess() failed!\n");
			}

			return ret;
		}
	}

	return 0;
}