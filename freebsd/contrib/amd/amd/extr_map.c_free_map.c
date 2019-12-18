#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* am_fd; scalar_t__ am_autofs_fh; int /*<<< orphan*/ ** am_alarray; int /*<<< orphan*/ * am_al; int /*<<< orphan*/ ** am_transp; int /*<<< orphan*/ ** am_pref; int /*<<< orphan*/ ** am_path; int /*<<< orphan*/ ** am_name; int /*<<< orphan*/ ** am_link; } ;
typedef  TYPE_1__ am_node ;
typedef  int /*<<< orphan*/  am_loc ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  XLOG_FATAL ; 
 int /*<<< orphan*/  autofs_release_fh (TYPE_1__*) ; 
 int /*<<< orphan*/  exported_ap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_loc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  remove_am (TYPE_1__*) ; 

void
free_map(am_node *mp)
{
  remove_am(mp);

  if (mp->am_fd[1] != -1)
    plog(XLOG_FATAL, "free_map: called prior to notifying the child for %s.",
	mp->am_path);

  XFREE(mp->am_link);
  XFREE(mp->am_name);
  XFREE(mp->am_path);
  XFREE(mp->am_pref);
  XFREE(mp->am_transp);

  if (mp->am_al)
    free_loc(mp->am_al);

  if (mp->am_alarray) {
    am_loc **temp_al;
    for (temp_al = mp->am_alarray; *temp_al; temp_al++)
      free_loc(*temp_al);
    XFREE(mp->am_alarray);
  }

#ifdef HAVE_FS_AUTOFS
  if (mp->am_autofs_fh)
    autofs_release_fh(mp);
#endif /* HAVE_FS_AUTOFS */

  exported_ap_free(mp);
}