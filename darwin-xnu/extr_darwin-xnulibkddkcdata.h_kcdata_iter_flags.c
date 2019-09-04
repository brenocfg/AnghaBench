#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {TYPE_1__* item; } ;
typedef  TYPE_2__ kcdata_iter_t ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t
kcdata_iter_flags(kcdata_iter_t iter)
{
	return iter.item->flags;
}