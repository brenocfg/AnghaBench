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
struct pcbit_dev {struct pcbit_chan* b2; struct pcbit_chan* b1; } ;
struct pcbit_chan {int dummy; } ;

/* Variables and functions */
 int MAX_PCBIT_CARDS ; 
 struct pcbit_dev** dev_pcbit ; 

__attribute__((used)) static __inline__ struct pcbit_dev * chan2dev(struct pcbit_chan * chan) 
{
        struct pcbit_dev * dev;
        int i;


        for (i=0; i<MAX_PCBIT_CARDS; i++)
                if ((dev=dev_pcbit[i]))
                        if (dev->b1 == chan || dev->b2 == chan)
                                return dev;
        return NULL;

}