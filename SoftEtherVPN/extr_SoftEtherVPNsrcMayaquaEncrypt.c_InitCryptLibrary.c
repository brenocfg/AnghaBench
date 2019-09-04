#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_load_crypto_strings () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  OpenSSL_InitLock () ; 
 int /*<<< orphan*/  OpenSSL_add_all_ciphers () ; 
 int /*<<< orphan*/  OpenSSL_add_all_digests () ; 
 int /*<<< orphan*/  RAND_poll () ; 
 int /*<<< orphan*/  Rand (char*,int) ; 
 int /*<<< orphan*/  SSL_get_ex_new_index (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int openssl_inited ; 
 int /*<<< orphan*/  openssl_lock ; 
 int /*<<< orphan*/  ssl_clientcert_index ; 

void InitCryptLibrary()
{
	char tmp[16];

//	RAND_Init_For_SoftEther()
	openssl_lock = NewLock();
	SSL_library_init();
	//OpenSSL_add_all_algorithms();
	OpenSSL_add_all_ciphers();
	OpenSSL_add_all_digests();
	ERR_load_crypto_strings();
	SSL_load_error_strings();

	ssl_clientcert_index = SSL_get_ex_new_index(0, "struct SslClientCertInfo *", NULL, NULL, NULL);

#ifdef	OS_UNIX
	{
		char *name1 = "/dev/random";
		char *name2 = "/dev/urandom";
		IO *o;
		o = FileOpen(name1, false);
		if (o == NULL)
		{
			o = FileOpen(name2, false);
			if (o == NULL)
			{
				UINT64 now = SystemTime64();
				BUF *b;
				UINT i;
				b = NewBuf();
				for (i = 0;i < 4096;i++)
				{
					UCHAR c = rand() % 256;
					WriteBuf(b, &c, 1);
				}
				WriteBuf(b, &now, sizeof(now));
				RAND_seed(b->Buf, b->Size);
				FreeBuf(b);
			}
			else
			{
				FileClose(o);
			}
		}
		else
		{
			FileClose(o);
		}
	}
#endif	// OS_UNIX

	RAND_poll();

#ifdef	OS_WIN32
//	RAND_screen();
#endif
	Rand(tmp, sizeof(tmp));
	OpenSSL_InitLock();

	openssl_inited = true;
}