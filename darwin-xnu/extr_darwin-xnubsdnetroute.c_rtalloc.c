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
struct route {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtalloc_ign (struct route*,int /*<<< orphan*/ ) ; 

void
rtalloc(struct route *ro)
{
	rtalloc_ign(ro, 0);
}