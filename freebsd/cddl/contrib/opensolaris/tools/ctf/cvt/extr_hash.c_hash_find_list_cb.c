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
struct hash_data {int (* hd_fun ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  hd_private; int /*<<< orphan*/  hd_key; TYPE_1__* hd_hash; } ;
struct TYPE_2__ {scalar_t__ (* h_cmp ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*) ; 
 int stub2 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hash_find_list_cb(void *node, void *arg)
{
	struct hash_data *hd = arg;
	int cbrc;
	int rc = 0;

	if (hd->hd_hash->h_cmp(hd->hd_key, node) == 0) {
		if ((cbrc = hd->hd_fun(node, hd->hd_private)) < 0)
			return (cbrc);
		rc += cbrc;
	}

	return (rc);
}