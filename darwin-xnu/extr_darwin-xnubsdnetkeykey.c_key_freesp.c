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
struct secpolicy {int refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYDEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEYDEBUG_IPSEC_STAMP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct secpolicy*) ; 
 int /*<<< orphan*/  key_delsp (struct secpolicy*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sadb_mutex ; 

void
key_freesp(
		   struct secpolicy *sp,
		   int locked)
{
	
	/* sanity check */
	if (sp == NULL)
		panic("key_freesp: NULL pointer is passed.\n");
	
	if (!locked)
		lck_mtx_lock(sadb_mutex);
	else
		LCK_MTX_ASSERT(sadb_mutex, LCK_MTX_ASSERT_OWNED);
	sp->refcnt--;
	KEYDEBUG(KEYDEBUG_IPSEC_STAMP,
	    printf("DP freesp cause refcnt--:%d SP:0x%llx\n",
	    sp->refcnt, (uint64_t)VM_KERNEL_ADDRPERM(sp)));
	
	if (sp->refcnt == 0)
		key_delsp(sp);
	if (!locked)
		lck_mtx_unlock(sadb_mutex);
	return;
}