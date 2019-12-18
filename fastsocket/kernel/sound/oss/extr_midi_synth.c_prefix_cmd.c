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
struct TYPE_2__ {int (* prefix_cmd ) (int,unsigned char) ;} ;

/* Variables and functions */
 TYPE_1__** midi_devs ; 
 int stub1 (int,unsigned char) ; 

__attribute__((used)) static int
prefix_cmd(int midi_dev, unsigned char status)
{
	if ((char *) midi_devs[midi_dev]->prefix_cmd == NULL)
		return 1;

	return midi_devs[midi_dev]->prefix_cmd(midi_dev, status);
}