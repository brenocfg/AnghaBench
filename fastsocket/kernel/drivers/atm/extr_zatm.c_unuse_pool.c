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
struct atm_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pool_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 TYPE_2__* ZATM_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  drain_free (struct atm_dev*,int) ; 

__attribute__((used)) static void unuse_pool(struct atm_dev *dev,int pool)
{
	if (!(--ZATM_DEV(dev)->pool_info[pool].ref_count))
		drain_free(dev,pool);
}