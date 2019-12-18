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
struct talitos_private {int features; scalar_t__ reg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ TALITOS_CCCR (int) ; 
 scalar_t__ TALITOS_CCCR_LO (int) ; 
 int TALITOS_CCCR_LO_CDIE ; 
 int TALITOS_CCCR_LO_CDWE ; 
 int TALITOS_CCCR_LO_EAE ; 
 int TALITOS_CCCR_LO_IWSE ; 
 int TALITOS_CCCR_RESET ; 
 int TALITOS_FTR_HW_AUTH_CHECK ; 
 unsigned int TALITOS_TIMEOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  setbits32 (scalar_t__,int) ; 

__attribute__((used)) static int reset_channel(struct device *dev, int ch)
{
	struct talitos_private *priv = dev_get_drvdata(dev);
	unsigned int timeout = TALITOS_TIMEOUT;

	setbits32(priv->reg + TALITOS_CCCR(ch), TALITOS_CCCR_RESET);

	while ((in_be32(priv->reg + TALITOS_CCCR(ch)) & TALITOS_CCCR_RESET)
	       && --timeout)
		cpu_relax();

	if (timeout == 0) {
		dev_err(dev, "failed to reset channel %d\n", ch);
		return -EIO;
	}

	/* set 36-bit addressing, done writeback enable and done IRQ enable */
	setbits32(priv->reg + TALITOS_CCCR_LO(ch), TALITOS_CCCR_LO_EAE |
		  TALITOS_CCCR_LO_CDWE | TALITOS_CCCR_LO_CDIE);

	/* and ICCR writeback, if available */
	if (priv->features & TALITOS_FTR_HW_AUTH_CHECK)
		setbits32(priv->reg + TALITOS_CCCR_LO(ch),
		          TALITOS_CCCR_LO_IWSE);

	return 0;
}