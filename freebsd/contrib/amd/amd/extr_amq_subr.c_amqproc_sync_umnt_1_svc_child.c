#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ voidp ;
struct svc_req {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  rv ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {int /*<<< orphan*/  au_etype; } ;
typedef  TYPE_1__ amq_sync_umnt ;
struct TYPE_8__ {scalar_t__* am_fd; } ;
typedef  TYPE_2__ am_node ;

/* Variables and functions */
 int /*<<< orphan*/  AMQ_UMNT_READ ; 
 TYPE_2__* find_ap (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int read (scalar_t__,TYPE_1__*,int) ; 

amq_sync_umnt *
amqproc_sync_umnt_1_svc_child(voidp argp, struct svc_req *rqstp)
{
  static amq_sync_umnt rv;
  amq_sync_umnt buf;
  ssize_t n;

  am_node *mp = find_ap(*(char **) argp);

  memset(&rv, 0, sizeof(rv));
  rv.au_etype = AMQ_UMNT_READ;
  if (mp && mp->am_fd[0] >= 0) {
    n = read(mp->am_fd[0], &buf, sizeof(buf));
    if (n == sizeof(buf))
      rv = buf;
  }
  return &rv;
}