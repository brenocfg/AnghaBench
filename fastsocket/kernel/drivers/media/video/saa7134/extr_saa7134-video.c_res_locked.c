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
struct saa7134_dev {unsigned int resources; } ;

/* Variables and functions */

__attribute__((used)) static int res_locked(struct saa7134_dev *dev, unsigned int bit)
{
	return (dev->resources & bit);
}