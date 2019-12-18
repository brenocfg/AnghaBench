#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct a2232memory {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;
struct TYPE_4__ {TYPE_1__ resource; } ;

/* Variables and functions */
 scalar_t__ ZTWO_VADDR (int /*<<< orphan*/ ) ; 
 TYPE_2__** zd_a2232 ; 

__attribute__((used)) static inline volatile struct a2232memory *a2232mem(unsigned int board)
{
	return (volatile struct a2232memory *)ZTWO_VADDR(zd_a2232[board]->resource.start);
}