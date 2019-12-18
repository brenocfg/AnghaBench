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
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_DEVAD_NONE ; 
 int cphy_mdio_write (struct cphy*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static inline int simple_mdio_write(struct cphy *cphy, int reg,
				    unsigned int val)
{
	return cphy_mdio_write(cphy, MDIO_DEVAD_NONE, reg, val);
}