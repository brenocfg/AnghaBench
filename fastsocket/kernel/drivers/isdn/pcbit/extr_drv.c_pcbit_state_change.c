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
struct pcbit_dev {int id; } ;
struct pcbit_chan {int id; } ;

/* Variables and functions */
 char** isdn_state_table ; 
 int /*<<< orphan*/  pcbit_logstat (struct pcbit_dev*,char*) ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,char*,char*,char*) ; 
 char* strisdnevent (unsigned short) ; 

void pcbit_state_change(struct pcbit_dev * dev, struct pcbit_chan * chan, 
			unsigned short i, unsigned short ev, unsigned short f)
{
	char buf[256];
  
	sprintf(buf, "change on device: %d channel:%d\n%s -> %s -> %s\n",
		dev->id, chan->id, 
		isdn_state_table[i], strisdnevent(ev), isdn_state_table[f]
		);

#ifdef DEBUG
	printk("%s", buf);
#endif

	pcbit_logstat(dev, buf);
}