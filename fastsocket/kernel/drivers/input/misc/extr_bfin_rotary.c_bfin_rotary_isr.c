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
struct platform_device {int dummy; } ;
struct bfin_rot {int /*<<< orphan*/  button_key; int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
#define  CZMII 131 
#define  DCII 130 
#define  ICII 129 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  UCII 128 
 int /*<<< orphan*/  W1LCNT_ZERO ; 
 int bfin_read_CNT_COUNTER () ; 
 int bfin_read_CNT_STATUS () ; 
 int /*<<< orphan*/  bfin_write_CNT_COMMAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_CNT_STATUS (int) ; 
 struct bfin_rot* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  report_key_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_rotary_event (struct bfin_rot*,int) ; 

__attribute__((used)) static irqreturn_t bfin_rotary_isr(int irq, void *dev_id)
{
	struct platform_device *pdev = dev_id;
	struct bfin_rot *rotary = platform_get_drvdata(pdev);
	int delta;

	switch (bfin_read_CNT_STATUS()) {

	case ICII:
		break;

	case UCII:
	case DCII:
		delta = bfin_read_CNT_COUNTER();
		if (delta)
			report_rotary_event(rotary, delta);
		break;

	case CZMII:
		report_key_event(rotary->input, rotary->button_key);
		break;

	default:
		break;
	}

	bfin_write_CNT_COMMAND(W1LCNT_ZERO);	/* Clear COUNTER */
	bfin_write_CNT_STATUS(-1);	/* Clear STATUS */

	return IRQ_HANDLED;
}