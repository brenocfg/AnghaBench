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
struct sg_mapping_iter {scalar_t__ length; scalar_t__ consumed; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_dwiter_next (struct sg_mapping_iter*) ; 

__attribute__((used)) static bool sg_dwiter_is_at_end(struct sg_mapping_iter *miter)
{
	return miter->length == miter->consumed && !sg_dwiter_next(miter);
}