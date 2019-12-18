#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_3__ {int /*<<< orphan*/  cfg; } ;
struct TYPE_4__ {TYPE_1__ elsa; } ;
struct IsdnCardState {scalar_t__ subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
 int ELIRQF_TIMER_RUN ; 
 int ELIRQF_TIMER_RUN_PCC8 ; 
 scalar_t__ ELSA_PCC8 ; 
 scalar_t__ ELSA_QS1000 ; 
 scalar_t__ ELSA_QS3000 ; 
 int bytein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
TimerRun(struct IsdnCardState *cs)
{
	register u_char v;

	v = bytein(cs->hw.elsa.cfg);
	if ((cs->subtyp == ELSA_QS1000) || (cs->subtyp == ELSA_QS3000))
		return (0 == (v & ELIRQF_TIMER_RUN));
	else if (cs->subtyp == ELSA_PCC8)
		return (v & ELIRQF_TIMER_RUN_PCC8);
	return (v & ELIRQF_TIMER_RUN);
}