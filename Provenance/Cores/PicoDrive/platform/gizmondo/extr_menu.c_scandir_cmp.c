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
struct my_dirent {scalar_t__ d_type; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scandir_cmp(const void *p1, const void *p2)
{
	struct my_dirent **d1 = (struct my_dirent **)p1, **d2 = (struct my_dirent **)p2;
	if ((*d1)->d_type == (*d2)->d_type) return strcasecmp((*d1)->d_name, (*d2)->d_name);
	if ((*d1)->d_type == DT_DIR) return -1; // put before
	if ((*d2)->d_type == DT_DIR) return  1;
	return strcasecmp((*d1)->d_name, (*d2)->d_name);
}