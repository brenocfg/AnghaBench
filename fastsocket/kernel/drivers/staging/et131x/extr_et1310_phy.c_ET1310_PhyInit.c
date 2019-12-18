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
typedef  size_t uint16_t ;
struct et131x_adapter {int dummy; } ;

/* Variables and functions */
 int** ConfigPhy ; 
 int /*<<< orphan*/  MiRead (struct et131x_adapter*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  MiWrite (struct et131x_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 int /*<<< orphan*/  PHY_DATA_REG ; 
 int /*<<< orphan*/  PHY_ID_1 ; 
 int /*<<< orphan*/  PHY_ID_2 ; 
 int /*<<< orphan*/  PHY_INDEX_REG ; 
 int /*<<< orphan*/  PHY_MPHY_CONTROL_REG ; 

void ET1310_PhyInit(struct et131x_adapter *etdev)
{
	uint16_t data, index;

	if (etdev == NULL)
		return;

	/* get the identity (again ?) */
	MiRead(etdev, PHY_ID_1, &data);
	MiRead(etdev, PHY_ID_2, &data);

	/* what does this do/achieve ? */
	MiRead(etdev, PHY_MPHY_CONTROL_REG, &data); /* should read 0002 */
	MiWrite(etdev, PHY_MPHY_CONTROL_REG,	0x0006);

	/* read modem register 0402, should I do something with the return
	   data ? */
	MiWrite(etdev, PHY_INDEX_REG, 0x0402);
	MiRead(etdev, PHY_DATA_REG, &data);

	/* what does this do/achieve ? */
	MiWrite(etdev, PHY_MPHY_CONTROL_REG, 0x0002);

	/* get the identity (again ?) */
	MiRead(etdev, PHY_ID_1, &data);
	MiRead(etdev, PHY_ID_2, &data);

	/* what does this achieve ? */
	MiRead(etdev, PHY_MPHY_CONTROL_REG, &data); /* should read 0002 */
	MiWrite(etdev, PHY_MPHY_CONTROL_REG, 0x0006);

	/* read modem register 0402, should I do something with
	   the return data? */
	MiWrite(etdev, PHY_INDEX_REG, 0x0402);
	MiRead(etdev, PHY_DATA_REG, &data);

	MiWrite(etdev, PHY_MPHY_CONTROL_REG, 0x0002);

	/* what does this achieve (should return 0x1040) */
	MiRead(etdev, PHY_CONTROL, &data);
	MiRead(etdev, PHY_MPHY_CONTROL_REG, &data); /* should read 0002 */
	MiWrite(etdev, PHY_CONTROL, 0x1840);

	MiWrite(etdev, PHY_MPHY_CONTROL_REG, 0x0007);

	/* here the writing of the array starts.... */
	index = 0;
	while (ConfigPhy[index][0] != 0x0000) {
		/* write value */
		MiWrite(etdev, PHY_INDEX_REG, ConfigPhy[index][0]);
		MiWrite(etdev, PHY_DATA_REG, ConfigPhy[index][1]);

		/* read it back */
		MiWrite(etdev, PHY_INDEX_REG, ConfigPhy[index][0]);
		MiRead(etdev, PHY_DATA_REG, &data);

		/* do a check on the value read back ? */
		index++;
	}
	/* here the writing of the array ends... */

	MiRead(etdev, PHY_CONTROL, &data);		/* 0x1840 */
	MiRead(etdev, PHY_MPHY_CONTROL_REG, &data);/* should read 0007 */
	MiWrite(etdev, PHY_CONTROL, 0x1040);
	MiWrite(etdev, PHY_MPHY_CONTROL_REG, 0x0002);
}