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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ tcam_sz; } ;
struct niu {TYPE_1__ clas; } ;

/* Variables and functions */

__attribute__((used)) static u16 tcam_get_size(struct niu *np)
{
	/* One entry reserved for IP fragment rule */
	return np->clas.tcam_sz - 1;
}