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
struct secasvar {int /*<<< orphan*/  ivlen; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_randomfill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sadb_mutex ; 

void
key_sa_stir_iv(
			   struct secasvar *sav)
{
	lck_mtx_lock(sadb_mutex);
	if (!sav->iv)
		panic("key_sa_stir_iv called with sav == NULL");
	key_randomfill(sav->iv, sav->ivlen);
	lck_mtx_unlock(sadb_mutex);
}