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

/* Variables and functions */
 int blacklist_sa (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

int
blacklist(int action, int rfd, const char *msg)
{
	return blacklist_sa(action, rfd, NULL, 0, msg);
}