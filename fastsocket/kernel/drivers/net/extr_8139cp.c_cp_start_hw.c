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
struct cp_private {int /*<<< orphan*/  cpcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cmd ; 
 int /*<<< orphan*/  CpCmd ; 
 int RxOn ; 
 int TxOn ; 
 int /*<<< orphan*/  cpw16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpw8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void cp_start_hw (struct cp_private *cp)
{
	cpw16(CpCmd, cp->cpcmd);
	cpw8(Cmd, RxOn | TxOn);
}