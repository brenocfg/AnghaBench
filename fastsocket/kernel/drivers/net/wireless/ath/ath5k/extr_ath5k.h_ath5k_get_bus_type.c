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
struct ath5k_hw {int dummy; } ;
typedef  enum ath_bus_type { ____Placeholder_ath_bus_type } ath_bus_type ;
struct TYPE_4__ {TYPE_1__* bus_ops; } ;
struct TYPE_3__ {int ath_bus_type; } ;

/* Variables and functions */
 TYPE_2__* ath5k_hw_common (struct ath5k_hw*) ; 

__attribute__((used)) static inline enum ath_bus_type ath5k_get_bus_type(struct ath5k_hw *ah)
{
	return ath5k_hw_common(ah)->bus_ops->ath_bus_type;
}