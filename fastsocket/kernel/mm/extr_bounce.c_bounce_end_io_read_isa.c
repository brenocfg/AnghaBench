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
 int /*<<< orphan*/  __bounce_end_io_read (struct bio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isa_page_pool ; 

__attribute__((used)) static void bounce_end_io_read_isa(struct bio *bio, int err)
{
	__bounce_end_io_read(bio, isa_page_pool, err);
}