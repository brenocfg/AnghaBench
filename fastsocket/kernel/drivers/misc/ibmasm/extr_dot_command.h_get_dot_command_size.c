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
struct dot_command_header {size_t command_size; size_t data_size; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t get_dot_command_size(void *buffer)
{
	struct dot_command_header *cmd = (struct dot_command_header *)buffer;
	return sizeof(struct dot_command_header) + cmd->command_size + cmd->data_size;
}