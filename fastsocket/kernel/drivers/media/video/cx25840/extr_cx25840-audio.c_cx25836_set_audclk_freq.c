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
typedef  int /*<<< orphan*/  u32 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int cx25840_set_audclk_freq (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cx25836_set_audclk_freq(struct i2c_client *client, u32 freq)
{
	return cx25840_set_audclk_freq(client, freq);
}