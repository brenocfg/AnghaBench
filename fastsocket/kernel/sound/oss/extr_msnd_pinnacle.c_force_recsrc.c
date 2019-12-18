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
struct TYPE_2__ {scalar_t__ recsrc; } ;

/* Variables and functions */
 TYPE_1__ dev ; 
 unsigned long set_recsrc (unsigned long) ; 

__attribute__((used)) static unsigned long force_recsrc(unsigned long recsrc)
{
	dev.recsrc = 0;
	return set_recsrc(recsrc);
}