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
struct TYPE_7__ {TYPE_1__* am_ysib; struct TYPE_7__* am_osib; TYPE_2__* am_parent; int /*<<< orphan*/  am_path; scalar_t__ am_child; } ;
typedef  TYPE_3__ am_node ;
struct TYPE_6__ {TYPE_3__* am_child; } ;
struct TYPE_5__ {TYPE_3__* am_osib; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remove_am(am_node *mp)
{
  /*
   * 1.  Consistency check
   */
  if (mp->am_child && mp->am_parent) {
    plog(XLOG_WARNING, "children of \"%s\" still exist - deleting anyway", mp->am_path);
  }

  /*
   * 2.  Update parent's child pointer
   */
  if (mp->am_parent && mp->am_parent->am_child == mp)
    mp->am_parent->am_child = mp->am_osib;

  /*
   * 3.  Unlink from sibling chain
   */
  if (mp->am_ysib)
    mp->am_ysib->am_osib = mp->am_osib;
  if (mp->am_osib)
    mp->am_osib->am_ysib = mp->am_ysib;
}