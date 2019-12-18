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
typedef  int /*<<< orphan*/  zprop_list_t ;
typedef  int /*<<< orphan*/  zpool_list_t ;
typedef  int /*<<< orphan*/  zpool_iter_f ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  pool_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pool_list_get (int,char**,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ pool_list_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int
for_each_pool(int argc, char **argv, boolean_t unavail,
    zprop_list_t **proplist, zpool_iter_f func, void *data)
{
	zpool_list_t *list;
	int ret = 0;

	if ((list = pool_list_get(argc, argv, proplist, &ret)) == NULL)
		return (1);

	if (pool_list_iter(list, unavail, func, data) != 0)
		ret = 1;

	pool_list_free(list);

	return (ret);
}