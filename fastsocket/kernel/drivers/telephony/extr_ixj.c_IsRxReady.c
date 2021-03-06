#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rxrdy; } ;
struct TYPE_7__ {TYPE_1__ bits; } ;
struct TYPE_8__ {TYPE_2__ hsr; int /*<<< orphan*/  rxreadycheck; } ;
typedef  TYPE_3__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  ixj_perfmon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixj_read_HSR (TYPE_3__*) ; 

__attribute__((used)) static inline int IsRxReady(IXJ *j)
{
	ixj_read_HSR(j);
	ixj_perfmon(j->rxreadycheck);
	return j->hsr.bits.rxrdy ? 1 : 0;
}