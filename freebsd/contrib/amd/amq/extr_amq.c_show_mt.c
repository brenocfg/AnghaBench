#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum show_opt { ____Placeholder_show_opt } show_opt ;
struct TYPE_4__ {struct TYPE_4__* mt_child; struct TYPE_4__* mt_next; } ;
typedef  TYPE_1__ amq_mount_tree ;

/* Variables and functions */
 int /*<<< orphan*/  show_mti (TYPE_1__*,int,int*,int*,int*) ; 

__attribute__((used)) static void
show_mt(amq_mount_tree *mt, enum show_opt e, int *mwid, int *dwid, int *pwid)
{
  while (mt) {
    show_mti(mt, e, mwid, dwid, pwid);
    show_mt(mt->mt_next, e, mwid, dwid, pwid);
    mt = mt->mt_child;
  }
}