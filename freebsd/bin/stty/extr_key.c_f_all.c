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
struct info {int /*<<< orphan*/  ldisc; int /*<<< orphan*/  win; int /*<<< orphan*/  t; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSD ; 
 int /*<<< orphan*/  print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
f_all(struct info *ip)
{
	print(&ip->t, &ip->win, ip->ldisc, BSD);
}