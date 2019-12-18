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
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bounce_end_io (struct bio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_pool ; 

__attribute__((used)) static void bounce_end_io_write(struct bio *bio, int err)
{
	bounce_end_io(bio, page_pool, err);
}