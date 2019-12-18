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
struct saa7146_dev {int dummy; } ;

/* Variables and functions */
 int saa7146_wait_for_debi_done_busyloop (struct saa7146_dev*,int,int) ; 
 int saa7146_wait_for_debi_done_sleep (struct saa7146_dev*,int,int) ; 

int saa7146_wait_for_debi_done(struct saa7146_dev *dev, int nobusyloop)
{
	if (nobusyloop)
		return saa7146_wait_for_debi_done_sleep(dev, 50000, 250000);
	else
		return saa7146_wait_for_debi_done_busyloop(dev, 50000, 250000);
}