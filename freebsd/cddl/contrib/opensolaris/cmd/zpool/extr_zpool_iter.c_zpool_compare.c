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
struct TYPE_2__ {int /*<<< orphan*/ * zn_handle; } ;
typedef  TYPE_1__ zpool_node_t ;
typedef  int /*<<< orphan*/  zpool_handle_t ;

/* Variables and functions */
 int strcmp (char const*,char const*) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zpool_compare(const void *larg, const void *rarg, void *unused)
{
	zpool_handle_t *l = ((zpool_node_t *)larg)->zn_handle;
	zpool_handle_t *r = ((zpool_node_t *)rarg)->zn_handle;
	const char *lname = zpool_get_name(l);
	const char *rname = zpool_get_name(r);

	return (strcmp(lname, rname));
}