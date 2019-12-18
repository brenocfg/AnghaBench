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
typedef  int /*<<< orphan*/  u32 ;
struct cphy {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_INT_CAUSE ; 
 int /*<<< orphan*/  ELMER0_GP_BIT6 ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_RXSTAT ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_STAT ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_TXSTAT ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int /*<<< orphan*/  cphy_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ t1_is_asic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_tpi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88x201x_interrupt_clear(struct cphy *cphy)
{
	u32 elmer;
	u32 val;

#ifdef MV88x2010_LINK_STATUS_BUGS
	/* Required to read twice before clear takes affect. */
	cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_RXSTAT, &val);
	cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_TXSTAT, &val);
	cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_STAT, &val);

	/* Read this register after the others above it else
	 * the register doesn't clear correctly.
	 */
	cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &val);
#endif

	/* Clear link status. */
	cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &val);
	/* Clear PHY LASI interrupts. */
	cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_STAT, &val);

#ifdef MV88x2010_LINK_STATUS_BUGS
	/* Do it again. */
	cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_RXSTAT, &val);
	cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_TXSTAT, &val);
#endif

	/* Clear Marvell interrupts through Elmer0. */
	if (t1_is_asic(cphy->adapter)) {
		t1_tpi_read(cphy->adapter, A_ELMER0_INT_CAUSE, &elmer);
		elmer |= ELMER0_GP_BIT6;
		t1_tpi_write(cphy->adapter, A_ELMER0_INT_CAUSE, elmer);
	}
	return 0;
}