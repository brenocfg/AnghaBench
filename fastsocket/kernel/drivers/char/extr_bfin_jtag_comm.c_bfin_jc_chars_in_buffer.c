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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfin_jc_write_buf ; 
 int circ_cnt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bfin_jc_chars_in_buffer(struct tty_struct *tty)
{
	return circ_cnt(&bfin_jc_write_buf);
}