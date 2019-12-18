#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int pulse; scalar_t__ duration; } ;
struct wbcir_data {int irdata_error; int irdata_active; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  dev; int /*<<< orphan*/  rxtrigger; scalar_t__ sbase; TYPE_1__ ev; } ;
struct pnp_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  WBCIR_BANK_0 ; 
 int WBCIR_IRQ_ERR ; 
 int WBCIR_IRQ_RX ; 
 scalar_t__ WBCIR_REG_SP3_ASCR ; 
 scalar_t__ WBCIR_REG_SP3_EIR ; 
 scalar_t__ WBCIR_REG_SP3_LSR ; 
 scalar_t__ WBCIR_REG_SP3_RXDATA ; 
 int WBCIR_RX_AVAIL ; 
 int /*<<< orphan*/  WBCIR_RX_DISABLE ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  insb (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  ir_raw_event_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_store (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 struct wbcir_data* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wbcir_select_bank (struct wbcir_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
wbcir_irq_handler(int irqno, void *cookie)
{
	struct pnp_dev *device = cookie;
	struct wbcir_data *data = pnp_get_drvdata(device);
	unsigned long flags;
	u8 irdata[8];
	u8 disable = true;
	u8 status;
	int i;

	spin_lock_irqsave(&data->spinlock, flags);

	wbcir_select_bank(data, WBCIR_BANK_0);

	status = inb(data->sbase + WBCIR_REG_SP3_EIR);

	if (!(status & (WBCIR_IRQ_RX | WBCIR_IRQ_ERR))) {
		spin_unlock_irqrestore(&data->spinlock, flags);
		return IRQ_NONE;
	}

	/* Check for e.g. buffer overflow */
	if (status & WBCIR_IRQ_ERR) {
		data->irdata_error = true;
		ir_raw_event_reset(data->dev);
	}

	if (!(status & WBCIR_IRQ_RX))
		goto out;

	if (!data->irdata_active) {
		data->irdata_active = true;
		led_trigger_event(data->rxtrigger, LED_FULL);
	}

	/* Since RXHDLEV is set, at least 8 bytes are in the FIFO */
	insb(data->sbase + WBCIR_REG_SP3_RXDATA, &irdata[0], 8);

	for (i = 0; i < 8; i++) {
		u8 pulse;
		u32 duration;

		if (irdata[i] != 0xFF && irdata[i] != 0x00)
			disable = false;

		if (data->irdata_error)
			continue;

		pulse = irdata[i] & 0x80 ? false : true;
		duration = (irdata[i] & 0x7F) * 10000; /* ns */

		if (data->ev.pulse != pulse) {
			if (data->ev.duration != 0) {
				ir_raw_event_store(data->dev, &data->ev);
				data->ev.duration = 0;
			}

			data->ev.pulse = pulse;
		}

		data->ev.duration += duration;
	}

	if (disable) {
		if (data->ev.duration != 0 && !data->irdata_error) {
			ir_raw_event_store(data->dev, &data->ev);
			data->ev.duration = 0;
		}

		/* Set RXINACTIVE */
		outb(WBCIR_RX_DISABLE, data->sbase + WBCIR_REG_SP3_ASCR);

		/* Drain the FIFO */
		while (inb(data->sbase + WBCIR_REG_SP3_LSR) & WBCIR_RX_AVAIL)
			inb(data->sbase + WBCIR_REG_SP3_RXDATA);

		ir_raw_event_reset(data->dev);
		data->irdata_error = false;
		data->irdata_active = false;
		led_trigger_event(data->rxtrigger, LED_OFF);
	}

	ir_raw_event_handle(data->dev);

out:
	spin_unlock_irqrestore(&data->spinlock, flags);
	return IRQ_HANDLED;
}