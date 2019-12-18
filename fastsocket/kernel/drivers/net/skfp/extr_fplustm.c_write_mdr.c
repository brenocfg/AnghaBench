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
typedef  int /*<<< orphan*/  u_long ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_NPP () ; 
 int /*<<< orphan*/  MDRW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_mdr(struct s_smc *smc, u_long val)
{
	CHECK_NPP() ;
	MDRW(val) ;
}