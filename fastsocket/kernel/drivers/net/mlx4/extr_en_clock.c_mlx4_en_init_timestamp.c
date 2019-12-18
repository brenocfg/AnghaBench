#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  mult; int /*<<< orphan*/  read; } ;
struct mlx4_en_dev {int /*<<< orphan*/  overflow_period; TYPE_2__ cycles; int /*<<< orphan*/  clock; struct mlx4_dev* dev; } ;
struct TYPE_5__ {int hca_core_clock; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKSOURCE_MASK (int) ; 
 int HZ ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  clocksource_khz2mult (int,int) ; 
 int /*<<< orphan*/  cyclecounter_cyc2ns (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_en_read_clock ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

void mlx4_en_init_timestamp(struct mlx4_en_dev *mdev)
{
	struct mlx4_dev *dev = mdev->dev;
	u64 ns;

	memset(&mdev->cycles, 0, sizeof(mdev->cycles));
	mdev->cycles.read = mlx4_en_read_clock;
	mdev->cycles.mask = CLOCKSOURCE_MASK(48);
	/* Using shift to make calculation more accurate. Since current HW
	 * clock frequency is 427 MHz, and cycles are given using a 48 bits
	 * register, the biggest shift when calculating using u64, is 14
	 * (max_cycles * multiplier < 2^64)
	 */
	mdev->cycles.shift = 14;
	mdev->cycles.mult =
		clocksource_khz2mult(1000 * dev->caps.hca_core_clock, mdev->cycles.shift);

	timecounter_init(&mdev->clock, &mdev->cycles,
			 ktime_to_ns(ktime_get_real()));

	/* Calculate period in seconds to call the overflow watchdog - to make
	 * sure counter is checked at least once every wrap around.
	 */
	ns = cyclecounter_cyc2ns(&mdev->cycles, mdev->cycles.mask);
	do_div(ns, NSEC_PER_SEC / 2 / HZ);
	mdev->overflow_period = ns;
}