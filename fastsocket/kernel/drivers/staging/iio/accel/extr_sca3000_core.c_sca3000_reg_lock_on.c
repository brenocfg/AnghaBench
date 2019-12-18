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
typedef  int u8 ;
struct sca3000_state {int dummy; } ;

/* Variables and functions */
 int SCA3000_LOCKED ; 
 int /*<<< orphan*/  SCA3000_REG_ADDR_STATUS ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int sca3000_read_data (struct sca3000_state*,int /*<<< orphan*/ ,int**,int) ; 

__attribute__((used)) static int sca3000_reg_lock_on(struct sca3000_state *st)
{
	u8 *rx;
	int ret;

	ret = sca3000_read_data(st, SCA3000_REG_ADDR_STATUS, &rx, 1);

	if (ret < 0)
		return ret;
	ret = !(rx[1] & SCA3000_LOCKED);
	kfree(rx);

	return ret;
}