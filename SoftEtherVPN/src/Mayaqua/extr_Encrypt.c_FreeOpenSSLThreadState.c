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
 int /*<<< orphan*/  CRYPTO_cleanup_all_ex_data () ; 
 int /*<<< orphan*/  ERR_remove_thread_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_thread_stop () ; 

void FreeOpenSSLThreadState()
{
#if OPENSSL_VERSION_NUMBER < 0x10100000L
	CRYPTO_cleanup_all_ex_data();
	ERR_remove_thread_state(NULL);
#else
#ifndef LIBRESSL_VERSION_NUMBER
	OPENSSL_thread_stop();
#endif
#endif
}