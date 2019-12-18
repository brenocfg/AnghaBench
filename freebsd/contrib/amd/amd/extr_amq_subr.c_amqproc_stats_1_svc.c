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
typedef  int /*<<< orphan*/  amq_mount_stats ;

/* Variables and functions */
 int /*<<< orphan*/  amd_stats ; 

amq_mount_stats *
amqproc_stats_1_svc(voidp argp, struct svc_req *rqstp)
{
  return (amq_mount_stats *) ((void *)&amd_stats);
}