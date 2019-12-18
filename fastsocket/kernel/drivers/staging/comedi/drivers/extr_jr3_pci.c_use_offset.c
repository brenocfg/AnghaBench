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
struct jr3_channel {int /*<<< orphan*/  command_word0; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_s16 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void use_offset(volatile struct jr3_channel *channel, short offset_num)
{
	set_s16(&channel->command_word0, 0x0600 + (offset_num & 0x000f));
}