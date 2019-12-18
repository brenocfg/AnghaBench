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
struct TYPE_2__ {int c_cflag; } ;
struct info {int set; TYPE_1__ t; scalar_t__ off; } ;

/* Variables and functions */
 int CS8 ; 
 int CSIZE ; 
 int PARENB ; 
 int /*<<< orphan*/  cfmakeraw (TYPE_1__*) ; 
 int /*<<< orphan*/  f_sane (struct info*) ; 

void
f_raw(struct info *ip)
{

	if (ip->off)
		f_sane(ip);
	else {
		cfmakeraw(&ip->t);
		ip->t.c_cflag &= ~(CSIZE|PARENB);
		ip->t.c_cflag |= CS8;
		ip->set = 1;
	}
}