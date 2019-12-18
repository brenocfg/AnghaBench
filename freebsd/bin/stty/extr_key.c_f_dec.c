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
typedef  void* u_char ;
struct TYPE_2__ {int c_lflag; int /*<<< orphan*/  c_iflag; void** c_cc; } ;
struct info {int set; TYPE_1__ t; } ;

/* Variables and functions */
 void* CTRL (char) ; 
 int ECHOCTL ; 
 int ECHOE ; 
 int ECHOKE ; 
 int ECHOPRT ; 
 int /*<<< orphan*/  IXANY ; 
 size_t VERASE ; 
 size_t VINTR ; 
 size_t VKILL ; 

void
f_dec(struct info *ip)
{

	ip->t.c_cc[VERASE] = (u_char)0177;
	ip->t.c_cc[VKILL] = CTRL('u');
	ip->t.c_cc[VINTR] = CTRL('c');
	ip->t.c_lflag &= ~ECHOPRT;
	ip->t.c_lflag |= ECHOE|ECHOKE|ECHOCTL;
	ip->t.c_iflag &= ~IXANY;
	ip->set = 1;
}