#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_7__ {int /*<<< orphan*/  fhh_id; int /*<<< orphan*/  fhh_pid; } ;
struct TYPE_8__ {TYPE_1__ s; int /*<<< orphan*/  fhh_path; } ;
struct am_fh3 {TYPE_2__ u; int /*<<< orphan*/  fhh_gen; } ;
struct TYPE_9__ {int /*<<< orphan*/  am_mapno; int /*<<< orphan*/  am_path; int /*<<< orphan*/  am_gen; } ;
typedef  TYPE_3__ am_node ;
struct TYPE_10__ {int /*<<< orphan*/  am_fh3_length; scalar_t__ am_fh3_data; } ;
typedef  TYPE_4__ am_nfs_fh3 ;

/* Variables and functions */
 int /*<<< orphan*/  AM_FHSIZE3 ; 
 int /*<<< orphan*/  get_server_pid () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

void
mp_to_fh3(am_node *mp, am_nfs_fh3 *fhp)
{
  u_int pathlen;
  struct am_fh3 *fp = (struct am_fh3 *) fhp->am_fh3_data;

  memset((char *) fhp, 0, sizeof(am_nfs_fh3));
  fhp->am_fh3_length = AM_FHSIZE3;

  /* Store the generation number */
  fp->fhh_gen = mp->am_gen;

  pathlen = strlen(mp->am_path);
  if (pathlen <= sizeof(*fp) - sizeof(fp->fhh_gen)) {
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