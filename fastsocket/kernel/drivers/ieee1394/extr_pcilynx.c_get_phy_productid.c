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
typedef  int u32 ;
struct ti_lynx {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int get_phy_reg (struct ti_lynx*,int) ; 
 int /*<<< orphan*/  sel_phy_reg_page (struct ti_lynx*,int) ; 

__attribute__((used)) static u32 get_phy_productid(struct ti_lynx *lynx)
{
        u32 id = 0;
        sel_phy_reg_page(lynx, 1);
        id |= (get_phy_reg(lynx, 13) << 16);
        id |= (get_phy_reg(lynx, 14) << 8);
        id |= get_phy_reg(lynx, 15);
        PRINT(KERN_INFO, lynx->id, "PHY product id 0x%06x", id);
        return id;
}