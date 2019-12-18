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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  em28xx_videodbg (char*,unsigned int) ; 

__attribute__((used)) static void res_free(struct em28xx_fh *fh, unsigned int bits)
{
	struct em28xx    *dev = fh->dev;

	BUG_ON((fh->resources & bits) != bits);

	fh->resources  &= ~bits;
	dev->resources &= ~bits;
	em28xx_videodbg("res: put %d\n", bits);
}