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
struct ni_gpct {TYPE_1__* counter_dev; } ;
typedef  enum ni_gpct_register { ____Placeholder_ni_gpct_register } ni_gpct_register ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_register ) (struct ni_gpct*,unsigned int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NITIO_Num_Registers ; 
 int /*<<< orphan*/  stub1 (struct ni_gpct*,unsigned int,int) ; 

__attribute__((used)) static inline void write_register(struct ni_gpct *counter, unsigned bits,
				  enum ni_gpct_register reg)
{
	BUG_ON(reg >= NITIO_Num_Registers);
	counter->counter_dev->write_register(counter, bits, reg);
}