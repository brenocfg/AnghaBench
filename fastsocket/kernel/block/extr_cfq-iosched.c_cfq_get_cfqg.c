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
struct cfq_group {int dummy; } ;
struct cfq_data {struct cfq_group root_group; } ;

/* Variables and functions */

__attribute__((used)) static struct cfq_group *cfq_get_cfqg(struct cfq_data *cfqd)
{
	return &cfqd->root_group;
}