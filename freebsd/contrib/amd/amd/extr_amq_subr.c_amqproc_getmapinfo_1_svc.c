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
typedef  int /*<<< orphan*/  voidp ;
struct svc_req {int dummy; } ;
typedef  int /*<<< orphan*/  amq_map_info_list ;

/* Variables and functions */
 int /*<<< orphan*/  map_list_head ; 

amq_map_info_list *
amqproc_getmapinfo_1_svc(voidp argp, struct svc_req *rqstp)
{
  return (amq_map_info_list *) ((void *)&map_list_head);	/* XXX */
}