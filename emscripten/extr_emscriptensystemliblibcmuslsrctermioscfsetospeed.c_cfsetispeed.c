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
struct termios {int dummy; } ;
typedef  scalar_t__ speed_t ;

/* Variables and functions */
 int cfsetospeed (struct termios*,scalar_t__) ; 

int cfsetispeed(struct termios *tio, speed_t speed)
{
	return speed ? cfsetospeed(tio, speed) : 0;
}