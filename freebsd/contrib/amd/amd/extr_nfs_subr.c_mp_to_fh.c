#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_5__ {int /*<<< orphan*/  fhh_id; int /*<<< orphan*/  fhh_pid; } ;
struct TYPE_6__ {TYPE_1__ s; int /*<<< orphan*/  fhh_path; } ;
struct am_fh {TYPE_2__ u; int /*<<< orphan*/  fhh_gen; } ;
struct TYPE_7__ {int /*<<< orphan*/  am_mapno; int /*<<< orphan*/  am_path; int /*<<< orphan*/  am_gen; } ;
typedef  TYPE_3__ am_node ;
typedef  int /*<<< orphan*/  am_nfs_fh ;

/* Variables and functions */
 int /*<<< orphan*/  get_server_pid () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

void
mp_to_fh(am_node *mp, am_nfs_fh *fhp)
{
  u_int pathlen;
  struct am_fh *fp = (struct am_fh *) fhp;

  memset((char *) fhp, 0, sizeof(am_nfs_fh));

  /* Store the generation number */
  fp->fhh_gen = mp->am_gen;

  pathlen = strlen(mp->am_path);
  if (pathlen <= sizeof(*fhp) - sizeof(fp->fhh_gen)) {
    /* dlog("mp_to_fh: new filehandle: %s", mp->am_path); */

    /*
     * Because fhp is treated as a filehandle we use memcpy instead of
     * xstrlcpy.
     */
    memcpy(fp->u.fhh_path, mp->am_path, pathlen); /* making a filehandle */
  } else {
    /*
     * Take the process id
     */
    fp->u.s.fhh_pid = get_server_pid();

    /*
     * ... the map number
     */
    fp->u.s.fhh_id = mp->am_mapno;

    /*
     * ... and the generation number (previously stored)
     * to make a "unique" triple that will never
     * be reallocated except across reboots (which doesn't matter)
     * or if we are unlucky enough to be given the same
     * pid as a previous amd (very unlikely).
     */
    /* dlog("mp_to_fh: old filehandle: %d", fp->u.s.fhh_id); */
  }
}