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
struct wimax_dev {struct net_device* net_dev; } ;
struct net_device {int dummy; } ;
struct i2400m_tlv_media_status {int /*<<< orphan*/  media_status; } ;
struct i2400m {struct wimax_dev wimax_dev; } ;
struct device {int dummy; } ;
typedef  enum i2400m_media_status { ____Placeholder_i2400m_media_status } i2400m_media_status ;

/* Variables and functions */
#define  I2400M_MEDIA_STATUS_LINK_DOWN 130 
#define  I2400M_MEDIA_STATUS_LINK_RENEW 129 
#define  I2400M_MEDIA_STATUS_LINK_UP 128 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,struct i2400m_tlv_media_status const*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,struct i2400m_tlv_media_status const*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

__attribute__((used)) static
void i2400m_report_tlv_media_status(struct i2400m *i2400m,
				    const struct i2400m_tlv_media_status *ms)
{
	struct device *dev = i2400m_dev(i2400m);
	struct wimax_dev *wimax_dev = &i2400m->wimax_dev;
	struct net_device *net_dev = wimax_dev->net_dev;
	enum i2400m_media_status status = le32_to_cpu(ms->media_status);

	d_fnstart(3, dev, "(i2400m %p ms %p [%u])\n", i2400m, ms, status);

	switch (status) {
	case I2400M_MEDIA_STATUS_LINK_UP:
		netif_carrier_on(net_dev);
		break;
	case I2400M_MEDIA_STATUS_LINK_DOWN:
		netif_carrier_off(net_dev);
		break;
	/*
	 * This is the network telling us we need to retrain the DHCP
	 * lease -- so far, we are trusting the WiMAX Network Service
	 * in user space to pick this up and poke the DHCP client.
	 */
	case I2400M_MEDIA_STATUS_LINK_RENEW:
		netif_carrier_on(net_dev);
		break;
	default:
		dev_err(dev, "HW BUG? unknown media status %u\n",
			status);
	};
	d_fnend(3, dev, "(i2400m %p ms %p [%u]) = void\n",
		i2400m, ms, status);
}