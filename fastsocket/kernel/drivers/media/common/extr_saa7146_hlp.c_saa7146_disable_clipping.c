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
typedef  int u32 ;
struct saa7146_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_FORMAT_CTRL ; 
 int MASK_05 ; 
 int MASK_21 ; 
 int MASK_W1 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  MC2 ; 
 int saa7146_read (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void saa7146_disable_clipping(struct saa7146_dev *dev)
{
	u32 clip_format	= saa7146_read(dev, CLIP_FORMAT_CTRL);

	/* mask out relevant bits (=lower word)*/
	clip_format &= MASK_W1;

	/* upload clipping-registers*/
	saa7146_write(dev, CLIP_FORMAT_CTRL,clip_format);
	saa7146_write(dev, MC2, (MASK_05 | MASK_21));

	/* disable video dma2 */
	saa7146_write(dev, MC1, MASK_21);
}