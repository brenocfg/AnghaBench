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
struct hash_data {void* hd_ret; void* hd_key; int /*<<< orphan*/  hd_fun; int /*<<< orphan*/ * hd_hash; } ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  hash_find_first_cb ; 
 int hash_match (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,struct hash_data*) ; 

int
hash_find(hash_t *hash, void *key, void **value)
{
	int ret;
	struct hash_data hd;

	hd.hd_hash = hash;
	hd.hd_fun = hash_find_first_cb;
	hd.hd_key = key;

	ret = hash_match(hash, key, hash_find_first_cb, &hd);
	if (ret && value)
		*value = hd.hd_ret;

	return (ret);
}