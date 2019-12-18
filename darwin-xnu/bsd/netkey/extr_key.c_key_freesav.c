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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct secasvar {int refcnt; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYDEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEYDEBUG_IPSEC_STAMP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct secasvar*) ; 
 int /*<<< orphan*/  key_delsav (struct secasvar*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sadb_mutex ; 

void
key_freesav(
			struct secasvar *sav,
			int locked)
{
	
	/* sanity check */
	if (sav == NULL)
		panic("key_freesav: NULL pointer is passed.\n");
	
	if (!locked)
		lck_mtx_lock(sadb_mutex);
	else
		LCK_MTX_ASSERT(sadb_mutex, LCK_MTX_ASSERT_OWNED);
	sav->refcnt--;
	KEYDEBUG(KEYDEBUG_IPSEC_STAMP,
	    printf("DP freesav cause refcnt--:%d SA:0x%llx SPI %u\n",
	    sav->refcnt, (uint64_t)VM_KERNEL_ADDRPERM(sav),
	    (u_int32_t)ntohl(sav->spi)));
	
	if (sav->refcnt == 0)
		key_delsav(sav);
	if (!locked)
		lck_mtx_unlock(sadb_mutex);
	return;
}