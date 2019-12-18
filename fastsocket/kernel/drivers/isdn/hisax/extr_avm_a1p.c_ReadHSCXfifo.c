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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ avm; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ ADDRREG_OFFSET ; 
 scalar_t__ DATAREG_OFFSET ; 
 int HSCX_CH_DIFF ; 
 scalar_t__ HSCX_FIFO_OFFSET ; 
 int /*<<< orphan*/  byteout (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  insb (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
ReadHSCXfifo(struct IsdnCardState *cs, int hscx, u_char * data, int size)
{
	byteout(cs->hw.avm.cfg_reg+ADDRREG_OFFSET,
			HSCX_FIFO_OFFSET+hscx*HSCX_CH_DIFF);
	insb(cs->hw.avm.cfg_reg+DATAREG_OFFSET, data, size);
}