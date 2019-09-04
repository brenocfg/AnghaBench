#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int fqs_throttle; } ;
typedef  TYPE_2__ fq_if_t ;
struct TYPE_8__ {int /*<<< orphan*/  fcl_throttle_on; } ;
struct TYPE_10__ {TYPE_1__ fcl_stat; } ;
typedef  TYPE_3__ fq_if_classq_t ;

/* Variables and functions */
 int /*<<< orphan*/  fq_if_purge_classq (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void
fq_if_classq_suspend(fq_if_t *fqs, fq_if_classq_t *fq_cl)
{
	fq_if_purge_classq(fqs, fq_cl);
	fqs->fqs_throttle = 1;
	fq_cl->fcl_stat.fcl_throttle_on++;
}