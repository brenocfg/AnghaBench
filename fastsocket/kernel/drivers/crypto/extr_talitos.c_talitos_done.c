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
struct talitos_private {int num_channels; scalar_t__ reg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TALITOS_IMR ; 
 int /*<<< orphan*/  TALITOS_IMR_INIT ; 
 scalar_t__ TALITOS_IMR_LO ; 
 int /*<<< orphan*/  TALITOS_IMR_LO_INIT ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  flush_channel (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbits32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void talitos_done(unsigned long data)
{
	struct device *dev = (struct device *)data;
	struct talitos_private *priv = dev_get_drvdata(dev);
	int ch;

	for (ch = 0; ch < priv->num_channels; ch++)
		flush_channel(dev, ch, 0, 0);

	/* At this point, all completed channels have been processed.
	 * Unmask done interrupts for channels completed later on.
	 */
	setbits32(priv->reg + TALITOS_IMR, TALITOS_IMR_INIT);
	setbits32(priv->reg + TALITOS_IMR_LO, TALITOS_IMR_LO_INIT);
}