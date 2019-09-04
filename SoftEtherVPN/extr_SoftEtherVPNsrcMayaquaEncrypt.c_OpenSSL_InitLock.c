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
typedef  int UINT ;
typedef  int /*<<< orphan*/  LOCK ;

/* Variables and functions */
 int CRYPTO_num_locks () ; 
 int /*<<< orphan*/  CRYPTO_set_id_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_set_locking_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Malloc (int) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  OpenSSL_Id ; 
 int /*<<< orphan*/  OpenSSL_Lock ; 
 int ssl_lock_num ; 
 int /*<<< orphan*/ * ssl_lock_obj ; 

void OpenSSL_InitLock()
{
	UINT i;

	// Initialization of the lock object
	ssl_lock_num = CRYPTO_num_locks();
	ssl_lock_obj = Malloc(sizeof(LOCK *) * ssl_lock_num);
	for (i = 0;i < ssl_lock_num;i++)
	{
		ssl_lock_obj[i] = NewLock();
	}

	// Setting the lock function
	CRYPTO_set_locking_callback(OpenSSL_Lock);
	CRYPTO_set_id_callback(OpenSSL_Id);
}