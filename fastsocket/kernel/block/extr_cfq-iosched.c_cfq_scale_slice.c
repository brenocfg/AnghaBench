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
typedef  int u64 ;
struct cfq_group {int /*<<< orphan*/  weight; } ;

/* Variables and functions */
 int BLKIO_WEIGHT_DEFAULT ; 
 unsigned long CFQ_SERVICE_SHIFT ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 cfq_scale_slice(unsigned long delta, struct cfq_group *cfqg)
{
	u64 d = delta << CFQ_SERVICE_SHIFT;

	d = d * BLKIO_WEIGHT_DEFAULT;
	do_div(d, cfqg->weight);
	return d;
}