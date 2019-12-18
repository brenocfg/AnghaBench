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
typedef  int /*<<< orphan*/  u_char ;
struct IsdnCardState {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSCX_CMDR ; 
 int /*<<< orphan*/  MemWriteHSCX (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemwaitforCEC (struct IsdnCardState*,int) ; 

__attribute__((used)) static inline void
MemWriteHSCXCMDR(struct IsdnCardState *cs, int hscx, u_char data)
{
	MemwaitforCEC(cs, hscx);
	MemWriteHSCX(cs, hscx, HSCX_CMDR, data);
}