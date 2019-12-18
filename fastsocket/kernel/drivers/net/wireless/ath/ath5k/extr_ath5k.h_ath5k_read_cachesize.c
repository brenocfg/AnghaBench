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
struct ath_common {TYPE_1__* bus_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_cachesize ) (struct ath_common*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ath_common*,int*) ; 

__attribute__((used)) static inline void ath5k_read_cachesize(struct ath_common *common, int *csz)
{
	common->bus_ops->read_cachesize(common, csz);
}