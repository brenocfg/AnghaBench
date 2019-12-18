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
struct saa7146 {scalar_t__ user; } ;
struct file {struct saa7146* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7146_MC1 ; 
 int /*<<< orphan*/  saawrite (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa_release(struct file *file)
{
	struct saa7146 *saa = file->private_data;
	saa->user--;

	if (saa->user > 0)	/* still someone using device */
		return 0;
	saawrite(0x007f0000, SAA7146_MC1);	/* stop all overlay dma */
	return 0;
}