#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
struct svc_req {int dummy; } ;
typedef  int /*<<< orphan*/  amq_mount_tree_p ;
struct TYPE_3__ {int amq_mount_tree_list_len; int /*<<< orphan*/ * amq_mount_tree_list_val; } ;
typedef  TYPE_1__ amq_mount_tree_list ;
typedef  int /*<<< orphan*/  am_node ;

/* Variables and functions */
 int /*<<< orphan*/ * get_exported_ap (int /*<<< orphan*/ ) ; 

amq_mount_tree_list *
amqproc_export_1_svc(voidp argp, struct svc_req *rqstp)
{
  static amq_mount_tree_list aml;
  static am_node *mp;

  mp = get_exported_ap(0);
  aml.amq_mount_tree_list_val = (amq_mount_tree_p *) ((void *) &mp);
  aml.amq_mount_tree_list_len = 1;	/* XXX */

  return &aml;
}