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
typedef  scalar_t__ zd_addr_t ;
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int zd_ioread32_locked (struct zd_chip*,int*,scalar_t__) ; 

__attribute__((used)) static int read_values(struct zd_chip *chip, u8 *values, size_t count,
	               zd_addr_t e2p_addr, u32 guard)
{
	int r;
	int i;
	u32 v;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	for (i = 0;;) {
		r = zd_ioread32_locked(chip, &v,
			               (zd_addr_t)((u16)e2p_addr+i/2));
		if (r)
			return r;
		v -= guard;
		if (i+4 < count) {
			values[i++] = v;
			values[i++] = v >>  8;
			values[i++] = v >> 16;
			values[i++] = v >> 24;
			continue;
		}
		for (;i < count; i++)
			values[i] = v >> (8*(i%3));
		return 0;
	}
}