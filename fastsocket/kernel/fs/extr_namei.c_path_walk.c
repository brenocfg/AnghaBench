#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nameidata {int dummy; } ;
struct filename {int dummy; } ;
struct TYPE_2__ {scalar_t__ total_link_count; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int link_path_walk (struct filename*,struct nameidata*) ; 

__attribute__((used)) static int path_walk(struct filename *name, struct nameidata *nd)
{
	current->total_link_count = 0;
	return link_path_walk(name, nd);
}