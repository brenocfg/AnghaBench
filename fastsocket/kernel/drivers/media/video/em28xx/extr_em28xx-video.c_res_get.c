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
struct em28xx_fh {unsigned int resources; struct em28xx* dev; } ;
struct em28xx {unsigned int resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  em28xx_videodbg (char*,unsigned int) ; 

__attribute__((used)) static int res_get(struct em28xx_fh *fh, unsigned int bit)
{
	struct em28xx    *dev = fh->dev;

	if (fh->resources & bit)
		/* have it already allocated */
		return 1;

	/* is it free? */
	if (dev->resources & bit) {
		/* no, someone else uses it */
		return 0;
	}
	/* it's free, grab it */
	fh->resources  |= bit;
	dev->resources |= bit;
	em28xx_videodbg("res: get %d\n", bit);
	return 1;
}