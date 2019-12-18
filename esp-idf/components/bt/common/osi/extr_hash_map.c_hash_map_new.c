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
typedef  int /*<<< orphan*/  key_free_fn ;
typedef  int /*<<< orphan*/  key_equality_fn ;
typedef  int /*<<< orphan*/  hash_map_t ;
typedef  int /*<<< orphan*/  hash_index_fn ;
typedef  int /*<<< orphan*/  data_free_fn ;

/* Variables and functions */
 int /*<<< orphan*/ * hash_map_new_internal (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

hash_map_t *hash_map_new(
    size_t num_bucket,
    hash_index_fn hash_fn,
    key_free_fn key_fn,
    data_free_fn data_fn,
    key_equality_fn equality_fn)
{
    return hash_map_new_internal(num_bucket, hash_fn, key_fn, data_fn, equality_fn);
}