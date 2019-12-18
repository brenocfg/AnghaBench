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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ buffer_freed (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_freed (struct buffer_head*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  release_buffer_page (struct buffer_head*) ; 

__attribute__((used)) static void release_data_buffer(struct buffer_head *bh)
{
	if (buffer_freed(bh)) {
		clear_buffer_freed(bh);
		release_buffer_page(bh);
	} else
		put_bh(bh);
}