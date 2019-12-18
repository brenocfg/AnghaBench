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
struct throtl_data {int* nr_queued; } ;

/* Variables and functions */

__attribute__((used)) static inline int total_nr_queued(struct throtl_data *td)
{
	return (td->nr_queued[0] + td->nr_queued[1]);
}