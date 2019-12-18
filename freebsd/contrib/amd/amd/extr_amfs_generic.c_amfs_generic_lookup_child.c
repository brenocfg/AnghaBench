#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int am_error; int /*<<< orphan*/ ** am_alarray; TYPE_2__* am_al; } ;
typedef  TYPE_3__ am_node ;
typedef  int /*<<< orphan*/  am_loc ;
struct TYPE_11__ {TYPE_1__* al_mnt; } ;
struct TYPE_10__ {int mf_error; int /*<<< orphan*/  mf_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ FSRV_ISUP (int /*<<< orphan*/ ) ; 
#define  VLOOK_DELETE 129 
#define  VLOOK_LOOKUP 128 
 int /*<<< orphan*/ ** amfs_lookup_loc (TYPE_3__*,int*) ; 
 TYPE_3__* amfs_lookup_node (TYPE_3__*,char*,int*) ; 
 int /*<<< orphan*/  dlog (char*) ; 
 int /*<<< orphan*/  ereturn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_map (TYPE_3__*) ; 

am_node *
amfs_generic_lookup_child(am_node *mp, char *fname, int *error_return, int op)
{
  am_node *new_mp;
  am_loc **al_array;
  int mp_error;

  dlog("in amfs_generic_lookup_child");

  *error_return = 0;
  new_mp = amfs_lookup_node(mp, fname, error_return);

  /* return if we got an error */
  if (!new_mp || *error_return > 0)
    return new_mp;

  /* also return if it's already mounted and known to be up */
  if (*error_return == 0 && FSRV_ISUP(new_mp->am_al->al_mnt->mf_server))
    return new_mp;

  switch (op) {
  case VLOOK_DELETE:
    /*
     * If doing a delete then don't create again!
     */
    ereturn(ENOENT);
  case VLOOK_LOOKUP:
    return new_mp;
  }

  /* save error_return */
  mp_error = *error_return;

  al_array = amfs_lookup_loc(new_mp, error_return);
  if (!al_array) {
    new_mp->am_error = new_mp->am_al->al_mnt->mf_error = *error_return;
    free_map(new_mp);
    return NULL;
  }

  /* store the array inside the am_node */
  new_mp->am_alarray = al_array;

  /*
   * Note: while it might seem like a good idea to prioritize
   * the list of mntfs's we got here, it probably isn't.
   * It would ignore the ordering of entries specified by the user,
   * which is counterintuitive and confusing.
   */
  return new_mp;
}