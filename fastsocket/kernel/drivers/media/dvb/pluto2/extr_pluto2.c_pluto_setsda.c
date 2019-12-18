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
 int /*<<< orphan*/  SLCS_SDA ; 
 int /*<<< orphan*/  pluto_rw (struct pluto*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pluto_setsda(void *data, int state)
{
	struct pluto *pluto = data;

	if (state)
		pluto_rw(pluto, REG_SLCS, SLCS_SDA, SLCS_SDA);
	else
		pluto_rw(pluto, REG_SLCS, SLCS_SDA, 0);
}