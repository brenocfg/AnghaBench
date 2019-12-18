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
struct TYPE_2__ {int /*<<< orphan*/ * c_cc; } ;
struct info {int set; TYPE_1__ t; } ;

/* Variables and functions */
 int /*<<< orphan*/  CERASE ; 
 int /*<<< orphan*/  CKILL ; 
 size_t VERASE ; 
 size_t VKILL ; 

void
f_ek(struct info *ip)
{

	ip->t.c_cc[VERASE] = CERASE;
	ip->t.c_cc[VKILL] = CKILL;
	ip->set = 1;
}