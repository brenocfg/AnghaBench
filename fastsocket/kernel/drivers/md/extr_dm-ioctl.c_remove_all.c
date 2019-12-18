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
struct dm_ioctl {scalar_t__ data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_hash_remove_all (int) ; 

__attribute__((used)) static int remove_all(struct dm_ioctl *param, size_t param_size)
{
	dm_hash_remove_all(1);
	param->data_size = 0;
	return 0;
}