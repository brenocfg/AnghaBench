#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ le_next; scalar_t__ le_prev; } ;
struct secasvar {scalar_t__ refcnt; struct secasvar* iv; struct secasvar* lft_s; struct secasvar* lft_h; struct secasvar* lft_c; int /*<<< orphan*/ * replay; struct secasvar* sched; int /*<<< orphan*/  schedlen; struct secasvar* key_enc; struct secasvar* key_auth; TYPE_1__ spihash; } ;

/* Variables and functions */
 int /*<<< orphan*/  KFREE (struct secasvar*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LIST_REMOVE (struct secasvar*,int /*<<< orphan*/ ) ; 
 struct secasvar* _KEYBUF (struct secasvar*) ; 
 int /*<<< orphan*/  _KEYLEN (struct secasvar*) ; 
 scalar_t__ __LIST_CHAINED (struct secasvar*) ; 
 int /*<<< orphan*/  bzero (struct secasvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  ipsec_sav_count ; 
 int /*<<< orphan*/  keydb_delsecreplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sadb_mutex ; 
 int /*<<< orphan*/  spihash ; 

void
key_delsav(
		   struct secasvar *sav)
{
	
	LCK_MTX_ASSERT(sadb_mutex, LCK_MTX_ASSERT_OWNED);
	
	/* sanity check */
	if (sav == NULL)
		panic("key_delsav: NULL pointer is passed.\n");
	
	if (sav->refcnt > 0)
		return;		/* can't free */
	
	/* remove from SA header */
	if (__LIST_CHAINED(sav))
		LIST_REMOVE(sav, chain);
	ipsec_sav_count--;
	
	if (sav->spihash.le_prev || sav->spihash.le_next)
		LIST_REMOVE(sav, spihash);
	
	if (sav->key_auth != NULL) {
		bzero(_KEYBUF(sav->key_auth), _KEYLEN(sav->key_auth));
		KFREE(sav->key_auth);
		sav->key_auth = NULL;
	}
	if (sav->key_enc != NULL) {
		bzero(_KEYBUF(sav->key_enc), _KEYLEN(sav->key_enc));
		KFREE(sav->key_enc);
		sav->key_enc = NULL;
	}
	if (sav->sched) {
		bzero(sav->sched, sav->schedlen);
		KFREE(sav->sched);
		sav->sched = NULL;
	}
	if (sav->replay != NULL) {
		keydb_delsecreplay(sav->replay);
		sav->replay = NULL;
	}
	if (sav->lft_c != NULL) {
		KFREE(sav->lft_c);
		sav->lft_c = NULL;
	}
	if (sav->lft_h != NULL) {
		KFREE(sav->lft_h);
		sav->lft_h = NULL;
	}
	if (sav->lft_s != NULL) {
		KFREE(sav->lft_s);
		sav->lft_s = NULL;
	}
	if (sav->iv != NULL) {
		KFREE(sav->iv);
		sav->iv = NULL;
	}
	
	KFREE(sav);
	
	return;
}