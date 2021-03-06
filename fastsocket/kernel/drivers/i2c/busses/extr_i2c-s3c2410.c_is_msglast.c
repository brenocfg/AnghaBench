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
struct s3c24xx_i2c {int msg_ptr; TYPE_1__* msg; } ;
struct TYPE_2__ {int len; } ;

/* Variables and functions */

__attribute__((used)) static inline int is_msglast(struct s3c24xx_i2c *i2c)
{
	return i2c->msg_ptr == i2c->msg->len-1;
}