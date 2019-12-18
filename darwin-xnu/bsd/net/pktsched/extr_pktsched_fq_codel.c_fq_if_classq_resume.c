#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ fqs_throttle; } ;
typedef  TYPE_2__ fq_if_t ;
struct TYPE_7__ {int /*<<< orphan*/  fcl_throttle_off; } ;
struct TYPE_9__ {TYPE_1__ fcl_stat; } ;
typedef  TYPE_3__ fq_if_classq_t ;

/* Variables and functions */
 int /*<<< orphan*/  FQ_IF_CLASSQ_IDLE (TYPE_3__*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fq_if_classq_resume(fq_if_t *fqs, fq_if_classq_t *fq_cl)
{
	VERIFY(FQ_IF_CLASSQ_IDLE(fq_cl));
	fqs->fqs_throttle = 0;
	fq_cl->fcl_stat.fcl_throttle_off++;
}