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
struct IR_i2c {int dummy; } ;

/* Variables and functions */
 int get_key_haup_common (struct IR_i2c*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_key_haup(struct IR_i2c *ir, u32 *ir_key, u32 *ir_raw)
{
	return get_key_haup_common (ir, ir_key, ir_raw, 3, 0);
}