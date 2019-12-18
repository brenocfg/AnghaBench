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
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct k8temp_data {int valid; int sensorsp; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; int /*<<< orphan*/ ** temp; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  REG_TEMP ; 
 int SEL_CORE ; 
 int SEL_PLACE ; 
 struct k8temp_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static struct k8temp_data *k8temp_update_device(struct device *dev)
{
	struct k8temp_data *data = dev_get_drvdata(dev);
	struct pci_dev *pdev = to_pci_dev(dev);
	u8 tmp;

	mutex_lock(&data->update_lock);

	if (!data->valid
	    || time_after(jiffies, data->last_updated + HZ)) {
		pci_read_config_byte(pdev, REG_TEMP, &tmp);
		tmp &= ~(SEL_PLACE | SEL_CORE);		/* Select sensor 0, core0 */
		pci_write_config_byte(pdev, REG_TEMP, tmp);
		pci_read_config_dword(pdev, REG_TEMP, &data->temp[0][0]);

		if (data->sensorsp & SEL_PLACE) {
			tmp |= SEL_PLACE;	/* Select sensor 1, core0 */
			pci_write_config_byte(pdev, REG_TEMP, tmp);
			pci_read_config_dword(pdev, REG_TEMP,
					      &data->temp[0][1]);
		}

		if (data->sensorsp & SEL_CORE) {
			tmp &= ~SEL_PLACE;	/* Select sensor 0, core1 */
			tmp |= SEL_CORE;
			pci_write_config_byte(pdev, REG_TEMP, tmp);
			pci_read_config_dword(pdev, REG_TEMP,
					      &data->temp[1][0]);

			if (data->sensorsp & SEL_PLACE) {
				tmp |= SEL_PLACE;	/* Select sensor 1, core1 */
				pci_write_config_byte(pdev, REG_TEMP, tmp);
				pci_read_config_dword(pdev, REG_TEMP,
						      &data->temp[1][1]);
			}
		}

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);
	return data;
}