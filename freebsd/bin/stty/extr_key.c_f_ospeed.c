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
struct info {int set; int /*<<< orphan*/  arg; int /*<<< orphan*/  t; } ;
typedef  int /*<<< orphan*/  speed_t ;

/* Variables and functions */
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfsetospeed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
f_ospeed(struct info *ip)
{

	cfsetospeed(&ip->t, (speed_t)atoi(ip->arg));
	ip->set = 1;
}