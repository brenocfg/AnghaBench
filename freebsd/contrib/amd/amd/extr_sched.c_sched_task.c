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
typedef  int /*<<< orphan*/  wchan_t ;
struct TYPE_3__ {scalar_t__ w; scalar_t__ pid; int /*<<< orphan*/  wchan; } ;
typedef  TYPE_1__ pjob ;
typedef  int /*<<< orphan*/  opaque_t ;
typedef  int /*<<< orphan*/  cb_fun ;

/* Variables and functions */
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* sched_job (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
sched_task(cb_fun *cf, opaque_t ca, wchan_t wchan)
{
  /*
   * Allocate a new task
   */
  pjob *p = sched_job(cf, ca);

  dlog("SLEEP on %p", wchan);
  p->wchan = wchan;
  p->pid = 0;
  p->w = 0;			/* was memset (when ->w was union) */
}