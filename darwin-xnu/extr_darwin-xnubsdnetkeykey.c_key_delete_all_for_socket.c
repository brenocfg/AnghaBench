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
typedef  size_t u_int ;
struct socket {int dummy; } ;
struct secasvar {int flags2; struct socket* so; int /*<<< orphan*/ * savtree; } ;
struct secashead {int flags2; struct socket* so; int /*<<< orphan*/ * savtree; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_SADB_LOCKED ; 
 struct secasvar* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct secasvar* LIST_NEXT (struct secasvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SADB_SASTATE_DEAD ; 
 int SADB_X_EXT_SA2_DELETE_ON_DETACH ; 
 size_t _ARRAYLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  key_freesav (struct secasvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_sa_chgstate (struct secasvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sahtree ; 
 int /*<<< orphan*/  saorder_state_alive ; 
 size_t* saorder_state_any ; 

__attribute__((used)) static void
key_delete_all_for_socket (struct socket *so)
{
	struct secashead *sah, *nextsah;
	struct secasvar *sav, *nextsav;
	u_int stateidx;
	u_int state;

	for (sah = LIST_FIRST(&sahtree);
		 sah != NULL;
		 sah = nextsah) {
		nextsah = LIST_NEXT(sah, chain);
		for (stateidx = 0; stateidx < _ARRAYLEN(saorder_state_alive); stateidx++) {
			state = saorder_state_any[stateidx];
			for (sav = LIST_FIRST(&sah->savtree[state]); sav != NULL; sav = nextsav) {
				nextsav = LIST_NEXT(sav, chain);
				if (sav->flags2 & SADB_X_EXT_SA2_DELETE_ON_DETACH &&
					sav->so == so) {
					key_sa_chgstate(sav, SADB_SASTATE_DEAD);
					key_freesav(sav, KEY_SADB_LOCKED);
				}
			}
		}
	}
}