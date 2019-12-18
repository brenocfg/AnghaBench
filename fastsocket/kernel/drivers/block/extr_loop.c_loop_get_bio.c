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
struct loop_device {int /*<<< orphan*/  lo_bio_list; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct bio* bio_list_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bio *loop_get_bio(struct loop_device *lo)
{
	return bio_list_pop(&lo->lo_bio_list);
}