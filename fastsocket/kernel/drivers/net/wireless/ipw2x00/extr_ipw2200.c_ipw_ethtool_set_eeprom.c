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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ipw_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * eeprom; } ;
struct ethtool_eeprom {size_t offset; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPW_EEPROM_DATA ; 
 int IPW_EEPROM_IMAGE_SIZE ; 
 int /*<<< orphan*/  ipw_write8 (struct ipw_priv*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_ethtool_set_eeprom(struct net_device *dev,
				  struct ethtool_eeprom *eeprom, u8 * bytes)
{
	struct ipw_priv *p = libipw_priv(dev);
	int i;

	if (eeprom->offset + eeprom->len > IPW_EEPROM_IMAGE_SIZE)
		return -EINVAL;
	mutex_lock(&p->mutex);
	memcpy(&p->eeprom[eeprom->offset], bytes, eeprom->len);
	for (i = 0; i < IPW_EEPROM_IMAGE_SIZE; i++)
		ipw_write8(p, i + IPW_EEPROM_DATA, p->eeprom[i]);
	mutex_unlock(&p->mutex);
	return 0;
}