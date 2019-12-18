#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct spi_device {int /*<<< orphan*/  irq; } ;
struct ser_req {int /*<<< orphan*/  sample; int /*<<< orphan*/  msg; TYPE_1__* xfer; int /*<<< orphan*/  scratch; scalar_t__ ref_off; scalar_t__ command; scalar_t__ ref_on; } ;
struct device {int dummy; } ;
struct ads7846 {int model; int irq_disabled; int /*<<< orphan*/  vref_delay_usecs; } ;
struct TYPE_3__ {int len; int /*<<< orphan*/ * rx_buf; scalar_t__* tx_buf; int /*<<< orphan*/  delay_usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_CHANGE (TYPE_1__) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PWRDOWN ; 
 scalar_t__ REF_ON ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct ads7846* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ser_req*) ; 
 struct ser_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 
 int spi_sync (struct spi_device*,int /*<<< orphan*/ *) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int ads7846_read12_ser(struct device *dev, unsigned command)
{
	struct spi_device	*spi = to_spi_device(dev);
	struct ads7846		*ts = dev_get_drvdata(dev);
	struct ser_req		*req = kzalloc(sizeof *req, GFP_KERNEL);
	int			status;
	int			use_internal;

	if (!req)
		return -ENOMEM;

	spi_message_init(&req->msg);

	/* FIXME boards with ads7846 might use external vref instead ... */
	use_internal = (ts->model == 7846);

	/* maybe turn on internal vREF, and let it settle */
	if (use_internal) {
		req->ref_on = REF_ON;
		req->xfer[0].tx_buf = &req->ref_on;
		req->xfer[0].len = 1;
		spi_message_add_tail(&req->xfer[0], &req->msg);

		req->xfer[1].rx_buf = &req->scratch;
		req->xfer[1].len = 2;

		/* for 1uF, settle for 800 usec; no cap, 100 usec.  */
		req->xfer[1].delay_usecs = ts->vref_delay_usecs;
		spi_message_add_tail(&req->xfer[1], &req->msg);
	}

	/* take sample */
	req->command = (u8) command;
	req->xfer[2].tx_buf = &req->command;
	req->xfer[2].len = 1;
	spi_message_add_tail(&req->xfer[2], &req->msg);

	req->xfer[3].rx_buf = &req->sample;
	req->xfer[3].len = 2;
	spi_message_add_tail(&req->xfer[3], &req->msg);

	/* REVISIT:  take a few more samples, and compare ... */

	/* converter in low power mode & enable PENIRQ */
	req->ref_off = PWRDOWN;
	req->xfer[4].tx_buf = &req->ref_off;
	req->xfer[4].len = 1;
	spi_message_add_tail(&req->xfer[4], &req->msg);

	req->xfer[5].rx_buf = &req->scratch;
	req->xfer[5].len = 2;
	CS_CHANGE(req->xfer[5]);
	spi_message_add_tail(&req->xfer[5], &req->msg);

	ts->irq_disabled = 1;
	disable_irq(spi->irq);
	status = spi_sync(spi, &req->msg);
	ts->irq_disabled = 0;
	enable_irq(spi->irq);

	if (status == 0) {
		/* on-wire is a must-ignore bit, a BE12 value, then padding */
		status = be16_to_cpu(req->sample);
		status = status >> 3;
		status &= 0x0fff;
	}

	kfree(req);
	return status;
}