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
struct s_smc {int dummy; } ;

/* Variables and functions */
 int NUMPHYS ; 
 int /*<<< orphan*/  plc_init (struct s_smc*,int) ; 

__attribute__((used)) static void real_init_plc(struct s_smc *smc)
{
	int	p ;

	for (p = 0 ; p < NUMPHYS ; p++)
		plc_init(smc,p) ;
}