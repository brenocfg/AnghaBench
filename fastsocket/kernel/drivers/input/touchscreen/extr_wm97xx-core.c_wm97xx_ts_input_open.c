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
struct wm97xx {int ts_reader_min_interval; int ts_reader_interval; scalar_t__ pen_irq; int /*<<< orphan*/  ts_reader; int /*<<< orphan*/ * ts_workq; int /*<<< orphan*/  dev; scalar_t__ pen_is_down; int /*<<< orphan*/  pen_event_work; TYPE_2__* codec; TYPE_1__* mach_ops; } ;
struct input_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dig_enable ) (struct wm97xx*,int) ;int /*<<< orphan*/  (* acc_enable ) (struct wm97xx*,int) ;} ;
struct TYPE_3__ {scalar_t__ acc_enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct wm97xx* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct wm97xx*,int) ; 
 int /*<<< orphan*/  stub2 (struct wm97xx*,int) ; 
 int /*<<< orphan*/  wm97xx_init_pen_irq (struct wm97xx*) ; 
 int /*<<< orphan*/  wm97xx_pen_irq_worker ; 
 int /*<<< orphan*/  wm97xx_ts_reader ; 

__attribute__((used)) static int wm97xx_ts_input_open(struct input_dev *idev)
{
	struct wm97xx *wm = input_get_drvdata(idev);

	wm->ts_workq = create_singlethread_workqueue("kwm97xx");
	if (wm->ts_workq == NULL) {
		dev_err(wm->dev,
			"Failed to create workqueue\n");
		return -EINVAL;
	}

	/* start digitiser */
	if (wm->mach_ops && wm->mach_ops->acc_enabled)
		wm->codec->acc_enable(wm, 1);
	wm->codec->dig_enable(wm, 1);

	INIT_DELAYED_WORK(&wm->ts_reader, wm97xx_ts_reader);
	INIT_WORK(&wm->pen_event_work, wm97xx_pen_irq_worker);

	wm->ts_reader_min_interval = HZ >= 100 ? HZ / 100 : 1;
	if (wm->ts_reader_min_interval < 1)
		wm->ts_reader_min_interval = 1;
	wm->ts_reader_interval = wm->ts_reader_min_interval;

	wm->pen_is_down = 0;
	if (wm->pen_irq)
		wm97xx_init_pen_irq(wm);
	else
		dev_err(wm->dev, "No IRQ specified\n");

	/* If we either don't have an interrupt for pen down events or
	 * failed to acquire it then we need to poll.
	 */
	if (wm->pen_irq == 0)
		queue_delayed_work(wm->ts_workq, &wm->ts_reader,
				   wm->ts_reader_interval);

	return 0;
}