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
typedef  int /*<<< orphan*/  u32 ;
struct ioat_chan_common {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ IOAT_CHANERR_OFFSET ; 
 int /*<<< orphan*/  ioat2_quiesce (struct ioat_chan_common*,int /*<<< orphan*/ ) ; 
 int ioat2_reset_sync (struct ioat_chan_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ioat2_reset_hw(struct ioat_chan_common *chan)
{
	/* throw away whatever the channel was doing and get it initialized */
	u32 chanerr;

	ioat2_quiesce(chan, msecs_to_jiffies(100));

	chanerr = readl(chan->reg_base + IOAT_CHANERR_OFFSET);
	writel(chanerr, chan->reg_base + IOAT_CHANERR_OFFSET);

	return ioat2_reset_sync(chan, msecs_to_jiffies(200));
}