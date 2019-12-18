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

/* Variables and functions */
 int /*<<< orphan*/  CONF_modules_unload (int) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_cleanup () ; 
 int /*<<< orphan*/  ERR_free_strings () ; 
 int /*<<< orphan*/  EVP_cleanup () ; 
 int /*<<< orphan*/  FIPS_mode_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeOpenSSLThreadState () ; 
 int /*<<< orphan*/  OpenSSL_FreeLock () ; 
 int /*<<< orphan*/  SSL_COMP_free_compression_methods () ; 
 int openssl_inited ; 
 int /*<<< orphan*/ * openssl_lock ; 

void FreeCryptLibrary()
{
	openssl_inited = false;

	DeleteLock(openssl_lock);
	openssl_lock = NULL;
//	RAND_Free_For_SoftEther();
	OpenSSL_FreeLock();
#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
#ifdef OPENSSL_FIPS
	FIPS_mode_set(0);
#endif
#ifndef OPENSSL_NO_ENGINE
	ENGINE_cleanup();
#endif
	CONF_modules_unload(1);
	EVP_cleanup();

	FreeOpenSSLThreadState();

	ERR_free_strings();

#ifndef OPENSSL_NO_COMP
	SSL_COMP_free_compression_methods();
#endif
#endif
}