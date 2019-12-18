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
struct comedi_device {char const* board_name; } ;

/* Variables and functions */

const char *comedi_get_board_name(void *d)
{
	struct comedi_device *dev = (struct comedi_device *)d;

	return dev->board_name;
}