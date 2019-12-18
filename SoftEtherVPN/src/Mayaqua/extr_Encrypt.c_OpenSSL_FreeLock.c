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
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREADID_set_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_set_locking_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 size_t ssl_lock_num ; 
 int /*<<< orphan*/ * ssl_lock_obj ; 

void OpenSSL_FreeLock()
{
#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
	UINT i;

	for (i = 0;i < ssl_lock_num;i++)
	{
		DeleteLock(ssl_lock_obj[i]);
	}
	Free(ssl_lock_obj);
	ssl_lock_obj = NULL;

	CRYPTO_set_locking_callback(NULL);
	CRYPTO_THREADID_set_callback(NULL);
#endif
}