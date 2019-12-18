#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct aes_key_st {int dummy; } ;
typedef  int UINT ;
struct TYPE_3__ {int KeySize; void* DecryptKey; void* EncryptKey; int /*<<< orphan*/  KeyValue; } ;
typedef  TYPE_1__ AES_KEY_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  AES_set_decrypt_key (void*,int,void*) ; 
 int /*<<< orphan*/  AES_set_encrypt_key (void*,int,void*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,void*,int) ; 
 void* ZeroMalloc (int) ; 

AES_KEY_VALUE *AesNewKey(void *data, UINT size)
{
	AES_KEY_VALUE *k;
	// Validate arguments
	if (data == NULL || (!(size == 16 || size == 24 || size == 32)))
	{
		return NULL;
	}

	k = ZeroMalloc(sizeof(AES_KEY_VALUE));

	k->EncryptKey = ZeroMalloc(sizeof(struct aes_key_st));
	k->DecryptKey = ZeroMalloc(sizeof(struct aes_key_st));

	k->KeySize = size;
	Copy(k->KeyValue, data, size);

	AES_set_encrypt_key(data, size * 8, k->EncryptKey);
	AES_set_decrypt_key(data, size * 8, k->DecryptKey);

	return k;
}