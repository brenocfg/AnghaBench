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
typedef  int /*<<< orphan*/  SESSION ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  HUB ;
typedef  int /*<<< orphan*/  CONNECTION ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * NewServerSessionEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

SESSION *NewServerSession(CEDAR *cedar, CONNECTION *c, HUB *h, char *username, POLICY *policy)
{
	return NewServerSessionEx(cedar, c, h, username, policy, false, NULL);
}