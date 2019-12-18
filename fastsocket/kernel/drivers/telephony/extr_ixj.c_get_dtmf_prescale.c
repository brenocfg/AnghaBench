#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int high; int low; } ;
struct TYPE_6__ {TYPE_1__ ssr; } ;
typedef  TYPE_2__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  ixj_WriteDSPCommand (int,TYPE_2__*) ; 

__attribute__((used)) static int get_dtmf_prescale(IXJ *j)
{
	ixj_WriteDSPCommand(0xCF05, j);
	return j->ssr.high << 8 | j->ssr.low;
}