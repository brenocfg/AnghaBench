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
typedef  int u_long ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_TMRS ; 
 int /*<<< orphan*/  FM_TNEG ; 
 int inpw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_long mac_get_tneg(struct s_smc *smc)
{
	u_long	tneg ;

	tneg = (u_long)((long)inpw(FM_A(FM_TNEG))<<5) ;
	return((u_long)((tneg + ((inpw(FM_A(FM_TMRS))>>10)&0x1f)) |
		0xffe00000L)) ;
}