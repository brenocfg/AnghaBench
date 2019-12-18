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
typedef  int /*<<< orphan*/  Tree ;

/* Variables and functions */
 int /*<<< orphan*/  printed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printtree1 (int /*<<< orphan*/ ,int,int) ; 

void printtree(Tree p, int fd) {
	(void)printed(0);
	printtree1(p, fd, 1);
}