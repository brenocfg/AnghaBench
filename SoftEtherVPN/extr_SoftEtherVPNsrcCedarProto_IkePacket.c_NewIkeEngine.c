#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  des_key_sizes ;
typedef  int /*<<< orphan*/  des3_key_sizes ;
typedef  int /*<<< orphan*/  aes_key_sizes ;
typedef  int UINT ;
struct TYPE_7__ {int /*<<< orphan*/ ** EspDhs; int /*<<< orphan*/ ** IkeDhs; int /*<<< orphan*/ ** EspHashes; int /*<<< orphan*/ ** EspCryptos; int /*<<< orphan*/ ** IkeHashes; int /*<<< orphan*/ ** IkeCryptos; void* DhsList; void* HashesList; void* CryptosList; } ;
typedef  int /*<<< orphan*/  IKE_HASH ;
typedef  TYPE_1__ IKE_ENGINE ;
typedef  int /*<<< orphan*/  IKE_DH ;
typedef  int /*<<< orphan*/  IKE_CRYPTO ;

/* Variables and functions */
 int /*<<< orphan*/  IKE_CRYPTO_3DES_ID ; 
 int /*<<< orphan*/  IKE_CRYPTO_3DES_STRING ; 
 int /*<<< orphan*/  IKE_CRYPTO_AES_ID ; 
 int /*<<< orphan*/  IKE_CRYPTO_AES_STRING ; 
 int /*<<< orphan*/  IKE_CRYPTO_DES_ID ; 
 int /*<<< orphan*/  IKE_CRYPTO_DES_STRING ; 
 int /*<<< orphan*/  IKE_DH_1_ID ; 
 int /*<<< orphan*/  IKE_DH_1_STRING ; 
 int /*<<< orphan*/  IKE_DH_2048_ID ; 
 int /*<<< orphan*/  IKE_DH_2048_STRING ; 
 int /*<<< orphan*/  IKE_DH_2_ID ; 
 int /*<<< orphan*/  IKE_DH_2_STRING ; 
 int /*<<< orphan*/  IKE_DH_3072_ID ; 
 int /*<<< orphan*/  IKE_DH_3072_STRING ; 
 int /*<<< orphan*/  IKE_DH_4096_ID ; 
 int /*<<< orphan*/  IKE_DH_4096_STRING ; 
 int /*<<< orphan*/  IKE_DH_5_ID ; 
 int /*<<< orphan*/  IKE_DH_5_STRING ; 
 int /*<<< orphan*/  IKE_HASH_MD5_ID ; 
 int /*<<< orphan*/  IKE_HASH_MD5_STRING ; 
 int /*<<< orphan*/  IKE_HASH_SHA1_ID ; 
 int /*<<< orphan*/  IKE_HASH_SHA1_STRING ; 
 int /*<<< orphan*/  IKE_HASH_SHA2_256_ID ; 
 int /*<<< orphan*/  IKE_HASH_SHA2_256_STRING ; 
 int /*<<< orphan*/  IKE_HASH_SHA2_384_ID ; 
 int /*<<< orphan*/  IKE_HASH_SHA2_384_STRING ; 
 int /*<<< orphan*/  IKE_HASH_SHA2_512_ID ; 
 int /*<<< orphan*/  IKE_HASH_SHA2_512_STRING ; 
 size_t IKE_P1_CRYPTO_3DES_CBC ; 
 size_t IKE_P1_CRYPTO_AES_CBC ; 
 size_t IKE_P1_CRYPTO_DES_CBC ; 
 size_t IKE_P1_DH_GROUP_1024_MODP ; 
 size_t IKE_P1_DH_GROUP_1536_MODP ; 
 size_t IKE_P1_DH_GROUP_2048_MODP ; 
 size_t IKE_P1_DH_GROUP_3072_MODP ; 
 size_t IKE_P1_DH_GROUP_4096_MODP ; 
 size_t IKE_P1_DH_GROUP_768_MODP ; 
 size_t IKE_P1_HASH_MD5 ; 
 size_t IKE_P1_HASH_SHA1 ; 
 size_t IKE_P1_HASH_SHA2_256 ; 
 size_t IKE_P1_HASH_SHA2_384 ; 
 size_t IKE_P1_HASH_SHA2_512 ; 
 size_t IKE_P2_DH_GROUP_1024_MODP ; 
 size_t IKE_P2_DH_GROUP_1536_MODP ; 
 size_t IKE_P2_DH_GROUP_2048_MODP ; 
 size_t IKE_P2_DH_GROUP_3072_MODP ; 
 size_t IKE_P2_DH_GROUP_4096_MODP ; 
 size_t IKE_P2_DH_GROUP_768_MODP ; 
 size_t IKE_P2_HMAC_MD5_96 ; 
 size_t IKE_P2_HMAC_SHA1_96 ; 
 size_t IKE_TRANSFORM_ID_P2_ESP_3DES ; 
 size_t IKE_TRANSFORM_ID_P2_ESP_AES ; 
 size_t IKE_TRANSFORM_ID_P2_ESP_DES ; 
 int /*<<< orphan*/ * NewIkeCrypto (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/ * NewIkeDh (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * NewIkeHash (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

IKE_ENGINE *NewIkeEngine()
{
	IKE_ENGINE *e = ZeroMalloc(sizeof(IKE_ENGINE));
	IKE_CRYPTO *des, *des3, *aes;
	IKE_HASH *sha1, *md5, *sha2_256, *sha2_384, *sha2_512;
	IKE_DH *dh1, *dh2, *dh5, *dh2048, *dh3072, *dh4096;
	UINT des_key_sizes[] =
	{
		8,
	};
	UINT des3_key_sizes[] =
	{
		24,
	};
	UINT aes_key_sizes[] =
	{
		16, 24, 32,
	};

	e->CryptosList = NewListFast(NULL);
	e->HashesList = NewListFast(NULL);
	e->DhsList = NewListFast(NULL);

	//// Encryption algorithm
	// DES
	des = NewIkeCrypto(e, IKE_CRYPTO_DES_ID, IKE_CRYPTO_DES_STRING,
		des_key_sizes, sizeof(des_key_sizes) / sizeof(UINT), 8);

	// 3DES
	des3 = NewIkeCrypto(e, IKE_CRYPTO_3DES_ID, IKE_CRYPTO_3DES_STRING,
		des3_key_sizes, sizeof(des3_key_sizes) / sizeof(UINT), 8);

	// AES
	aes = NewIkeCrypto(e, IKE_CRYPTO_AES_ID, IKE_CRYPTO_AES_STRING,
		aes_key_sizes, sizeof(aes_key_sizes) / sizeof(UINT), 16);

	//// Hash algorithm
	// SHA-1
	sha1 = NewIkeHash(e, IKE_HASH_SHA1_ID, IKE_HASH_SHA1_STRING, 20);

	// SHA-2
	// sha2-256
	sha2_256 = NewIkeHash(e, IKE_HASH_SHA2_256_ID, IKE_HASH_SHA2_256_STRING, 32);
	// sha2-384
	sha2_384 = NewIkeHash(e, IKE_HASH_SHA2_384_ID, IKE_HASH_SHA2_384_STRING, 48);
	// sha2-512
	sha2_512 = NewIkeHash(e, IKE_HASH_SHA2_512_ID, IKE_HASH_SHA2_512_STRING, 64);

	// MD5
	md5 = NewIkeHash(e, IKE_HASH_MD5_ID, IKE_HASH_MD5_STRING, 16);

	//// DH algorithm
	dh1 = NewIkeDh(e, IKE_DH_1_ID, IKE_DH_1_STRING, 96);
	dh2 = NewIkeDh(e, IKE_DH_2_ID, IKE_DH_2_STRING, 128);
	dh5 = NewIkeDh(e, IKE_DH_5_ID, IKE_DH_5_STRING, 192);
	dh2048 = NewIkeDh(e, IKE_DH_2048_ID, IKE_DH_2048_STRING, 256);
	dh3072 = NewIkeDh(e, IKE_DH_3072_ID, IKE_DH_3072_STRING, 384);
	dh4096 = NewIkeDh(e, IKE_DH_4096_ID, IKE_DH_4096_STRING, 512);

	// Define the IKE algorithm
	e->IkeCryptos[IKE_P1_CRYPTO_DES_CBC] = des;
	e->IkeCryptos[IKE_P1_CRYPTO_3DES_CBC] = des3;
	e->IkeCryptos[IKE_P1_CRYPTO_AES_CBC] = aes;
	e->IkeHashes[IKE_P1_HASH_MD5] = md5;
	e->IkeHashes[IKE_P1_HASH_SHA1] = sha1;
	e->IkeHashes[IKE_P1_HASH_SHA2_256] = sha2_256;
	e->IkeHashes[IKE_P1_HASH_SHA2_384] = sha2_384;
	e->IkeHashes[IKE_P1_HASH_SHA2_512] = sha2_512;


	// Definition of ESP algorithm
	e->EspCryptos[IKE_TRANSFORM_ID_P2_ESP_DES] = des;
	e->EspCryptos[IKE_TRANSFORM_ID_P2_ESP_3DES] = des3;
	e->EspCryptos[IKE_TRANSFORM_ID_P2_ESP_AES] = aes;
	e->EspHashes[IKE_P2_HMAC_MD5_96] = md5;
	e->EspHashes[IKE_P2_HMAC_SHA1_96] = sha1;

	// Definition of the DH algorithm
	e->IkeDhs[IKE_P1_DH_GROUP_768_MODP] = e->EspDhs[IKE_P2_DH_GROUP_768_MODP] = dh1;
	e->IkeDhs[IKE_P1_DH_GROUP_1024_MODP] = e->EspDhs[IKE_P2_DH_GROUP_1024_MODP] = dh2;
	e->IkeDhs[IKE_P1_DH_GROUP_1536_MODP] = e->EspDhs[IKE_P2_DH_GROUP_1536_MODP] = dh5;
	e->IkeDhs[IKE_P1_DH_GROUP_2048_MODP] = e->EspDhs[IKE_P2_DH_GROUP_2048_MODP] = dh2048;
	e->IkeDhs[IKE_P1_DH_GROUP_3072_MODP] = e->EspDhs[IKE_P2_DH_GROUP_3072_MODP] = dh3072;
	e->IkeDhs[IKE_P1_DH_GROUP_4096_MODP] = e->EspDhs[IKE_P2_DH_GROUP_4096_MODP] = dh4096;

	return e;
}