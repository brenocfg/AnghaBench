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
typedef  int /*<<< orphan*/  u16 ;
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_GMAC_REG (unsigned int,int) ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gma_write16(const struct sky2_hw *hw, unsigned port, int r, u16 v)
{
	sky2_write16(hw, SK_GMAC_REG(port,r), v);
}