#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct cx231xx* priv; } ;
struct cx231xx_dvb {TYPE_1__ adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_pkt_size; } ;
struct cx231xx {int mode_tv; TYPE_2__ ts1_mode; int /*<<< orphan*/  i2c_lock; scalar_t__ USE_ISO; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX231XX_DIGITAL_MODE ; 
 int /*<<< orphan*/  CX231XX_DVB_MAX_PACKETS ; 
 int /*<<< orphan*/  CX231XX_DVB_NUM_BUFS ; 
 int /*<<< orphan*/  INDEX_TS1 ; 
 int /*<<< orphan*/  cx231xx_enable_i2c_port_3 (struct cx231xx*,int) ; 
 int /*<<< orphan*/  cx231xx_info (char*) ; 
 int cx231xx_init_bulk (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cx231xx_init_isoc (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_set_alt_setting (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int cx231xx_set_mode (struct cx231xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_bulk_copy ; 
 int /*<<< orphan*/  dvb_isoc_copy ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int start_streaming(struct cx231xx_dvb *dvb)
{
	int rc;
	struct cx231xx *dev = dvb->adapter.priv;

	if (dev->USE_ISO) {
		cx231xx_info("DVB transfer mode is ISO.\n");
		mutex_lock(&dev->i2c_lock);
		cx231xx_enable_i2c_port_3(dev, false);
		cx231xx_set_alt_setting(dev, INDEX_TS1, 4);
		cx231xx_enable_i2c_port_3(dev, true);
		mutex_unlock(&dev->i2c_lock);
		rc = cx231xx_set_mode(dev, CX231XX_DIGITAL_MODE);
		if (rc < 0)
			return rc;
		dev->mode_tv = 1;
		return cx231xx_init_isoc(dev, CX231XX_DVB_MAX_PACKETS,
					CX231XX_DVB_NUM_BUFS,
					dev->ts1_mode.max_pkt_size,
					dvb_isoc_copy);
	} else {
		cx231xx_info("DVB transfer mode is BULK.\n");
		cx231xx_set_alt_setting(dev, INDEX_TS1, 0);
		rc = cx231xx_set_mode(dev, CX231XX_DIGITAL_MODE);
		if (rc < 0)
			return rc;
		dev->mode_tv = 1;
		return cx231xx_init_bulk(dev, CX231XX_DVB_MAX_PACKETS,
					CX231XX_DVB_NUM_BUFS,
					dev->ts1_mode.max_pkt_size,
					dvb_bulk_copy);
	}

}