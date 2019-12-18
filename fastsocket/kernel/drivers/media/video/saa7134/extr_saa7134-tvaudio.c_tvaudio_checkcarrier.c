#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct saa7134_dev {TYPE_1__* tvnorm; } ;
struct mainscan {int carr; int std; int /*<<< orphan*/  name; } ;
typedef  int __s32 ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int SAA7134_LEVEL_READOUT1 ; 
 int /*<<< orphan*/  SCAN_SAMPLE_DELAY ; 
 int audio_debug ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int saa_readl (int) ; 
 int /*<<< orphan*/  tvaudio_setcarrier (struct saa7134_dev*,int,int) ; 
 scalar_t__ tvaudio_sleep (struct saa7134_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tvaudio_checkcarrier(struct saa7134_dev *dev, struct mainscan *scan)
{
	__s32 left,right,value;

	if (audio_debug > 1) {
		int i;
		dprintk("debug %d:",scan->carr);
		for (i = -150; i <= 150; i += 30) {
			tvaudio_setcarrier(dev,scan->carr+i,scan->carr+i);
			saa_readl(SAA7134_LEVEL_READOUT1 >> 2);
			if (tvaudio_sleep(dev,SCAN_SAMPLE_DELAY))
				return -1;
			value = saa_readl(SAA7134_LEVEL_READOUT1 >> 2);
			if (0 == i)
				printk("  #  %6d  # ",value >> 16);
			else
				printk(" %6d",value >> 16);
		}
		printk("\n");
	}
	if (dev->tvnorm->id & scan->std) {
		tvaudio_setcarrier(dev,scan->carr-90,scan->carr-90);
		saa_readl(SAA7134_LEVEL_READOUT1 >> 2);
		if (tvaudio_sleep(dev,SCAN_SAMPLE_DELAY))
			return -1;
		left = saa_readl(SAA7134_LEVEL_READOUT1 >> 2);

		tvaudio_setcarrier(dev,scan->carr+90,scan->carr+90);
		saa_readl(SAA7134_LEVEL_READOUT1 >> 2);
		if (tvaudio_sleep(dev,SCAN_SAMPLE_DELAY))
			return -1;
		right = saa_readl(SAA7134_LEVEL_READOUT1 >> 2);

		left >>= 16;
		right >>= 16;
		value = left > right ? left - right : right - left;
		dprintk("scanning %d.%03d MHz [%4s] =>  dc is %5d [%d/%d]\n",
			scan->carr / 1000, scan->carr % 1000,
			scan->name, value, left, right);
	} else {
		value = 0;
		dprintk("skipping %d.%03d MHz [%4s]\n",
			scan->carr / 1000, scan->carr % 1000, scan->name);
	}
	return value;
}