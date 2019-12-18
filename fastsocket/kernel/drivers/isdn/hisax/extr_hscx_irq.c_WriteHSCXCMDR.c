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
 int /*<<< orphan*/  WRITEHSCX (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitforCEC (struct IsdnCardState*,int) ; 

__attribute__((used)) static inline void
WriteHSCXCMDR(struct IsdnCardState *cs, int hscx, u_char data)
{
	waitforCEC(cs, hscx);
	WRITEHSCX(cs, hscx, HSCX_CMDR, data);
}