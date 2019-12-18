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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ds1wm_data {int bus_shift; scalar_t__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void ds1wm_write_register(struct ds1wm_data *ds1wm_data, u32 reg,
					u8 val)
{
	__raw_writeb(val, ds1wm_data->map + (reg << ds1wm_data->bus_shift));
}