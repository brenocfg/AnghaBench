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
struct buffer_head {int /*<<< orphan*/  b_assoc_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct buffer_head*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
init_buffer_head(void *data)
{
	struct buffer_head *bh = data;

	memset(bh, 0, sizeof(*bh));
	INIT_LIST_HEAD(&bh->b_assoc_buffers);
}