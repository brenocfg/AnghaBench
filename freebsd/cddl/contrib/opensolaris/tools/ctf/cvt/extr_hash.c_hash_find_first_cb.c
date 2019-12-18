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
struct hash_data {void* hd_ret; int /*<<< orphan*/  hd_key; TYPE_1__* hd_hash; } ;
struct TYPE_2__ {scalar_t__ (* h_cmp ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
hash_find_first_cb(void *node, void *arg)
{
	struct hash_data *hd = arg;
	if (hd->hd_hash->h_cmp(hd->hd_key, node) == 0) {
		hd->hd_ret = node;
		return (-1);
	}

	return (0);
}