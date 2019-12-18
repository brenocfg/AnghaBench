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

/* Variables and functions */
 int /*<<< orphan*/  amqproc_umnt_1_svc (int /*<<< orphan*/ ,struct svc_req*) ; 

int *
amqproc_sync_umnt_1_svc_parent(voidp argp, struct svc_req *rqstp)
{
  amqproc_umnt_1_svc(argp, rqstp);
  return NULL;
}