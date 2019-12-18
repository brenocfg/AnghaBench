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
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  inferior_ptid ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_inferior_ptid ; 
 int /*<<< orphan*/ * xmalloc (int) ; 

struct cleanup *
save_inferior_ptid (void)
{
  ptid_t *saved_ptid_ptr;

  saved_ptid_ptr = xmalloc (sizeof (ptid_t));
  *saved_ptid_ptr = inferior_ptid;
  return make_cleanup (restore_inferior_ptid, saved_ptid_ptr);
}