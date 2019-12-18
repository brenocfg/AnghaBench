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
struct s6gmac {int dummy; } ;
struct mii_bus {struct s6gmac* priv; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  PHY_INIT_TIMEOUT ; 
 scalar_t__ s6mii_busy (struct s6gmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6mii_enable (struct s6gmac*) ; 

__attribute__((used)) static int s6mii_reset(struct mii_bus *bus)
{
	struct s6gmac *pd = bus->priv;
	s6mii_enable(pd);
	if (s6mii_busy(pd, PHY_INIT_TIMEOUT))
		return -ETIME;
	return 0;
}