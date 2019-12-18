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
struct TYPE_2__ {int c_iflag; int c_lflag; int /*<<< orphan*/  c_oflag; } ;
struct info {int set; TYPE_1__ t; scalar_t__ off; } ;

/* Variables and functions */
 int BRKINT ; 
 int ICANON ; 
 int IEXTEN ; 
 int IMAXBEL ; 
 int ISIG ; 
 int IXON ; 
 int /*<<< orphan*/  OPOST ; 
 int /*<<< orphan*/  f_sane (struct info*) ; 

void
f_cbreak(struct info *ip)
{

	if (ip->off)
		f_sane(ip);
	else {
		ip->t.c_iflag |= BRKINT|IXON|IMAXBEL;
		ip->t.c_oflag |= OPOST;
		ip->t.c_lflag |= ISIG|IEXTEN;
		ip->t.c_lflag &= ~ICANON;
		ip->set = 1;
	}
}