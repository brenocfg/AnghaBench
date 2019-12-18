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
struct tsl2561_command {int cmd; scalar_t__ clear; scalar_t__ word; scalar_t__ block; scalar_t__ address; } ;

/* Variables and functions */

__attribute__((used)) static inline void tsl2561_init_command_buf(struct tsl2561_command *buf)
{
	buf->address = 0;
	buf->block = 0;
	buf->word = 0;
	buf->clear = 0;
	buf->cmd = 1;
}