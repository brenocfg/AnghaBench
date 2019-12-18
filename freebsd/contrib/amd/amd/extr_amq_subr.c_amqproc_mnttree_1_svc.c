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
typedef  scalar_t__ voidp ;
struct svc_req {int dummy; } ;
typedef  int /*<<< orphan*/  amq_mount_tree_p ;
typedef  int /*<<< orphan*/  am_node ;

/* Variables and functions */
 int /*<<< orphan*/ * find_ap (char*) ; 

amq_mount_tree_p *
amqproc_mnttree_1_svc(voidp argp, struct svc_req *rqstp)
{
  static am_node *mp;

  mp = find_ap(*(char **) argp);
  return (amq_mount_tree_p *) ((void *)&mp);
}