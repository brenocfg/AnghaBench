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
struct pluto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SLCS ; 
 int SLCS_SCL ; 
 int pluto_readreg (struct pluto*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pluto_getscl(void *data)
{
	struct pluto *pluto = data;

	return pluto_readreg(pluto, REG_SLCS) & SLCS_SCL;
}