#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int msh2_khz; int ssh2_khz; } ;

/* Variables and functions */
 int MA_32XOPT_MSH2_CYCLES ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  sprintf (char const*,char*,int) ; 
 char const* static_buff ; 

__attribute__((used)) static const char *mgn_opt_sh2cycles(int id, int *offs)
{
	int khz = (id == MA_32XOPT_MSH2_CYCLES) ?
		currentConfig.msh2_khz : currentConfig.ssh2_khz;

	sprintf(static_buff, "%d", khz);
	return static_buff;
}