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
struct scatterlist {int /*<<< orphan*/  length; } ;
struct pohmelfs_crypto_engine {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int crypto_hash_update (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pohmelfs_hash_iterator(struct pohmelfs_crypto_engine *e,
		struct scatterlist *sg_dst, struct scatterlist *sg_src)
{
	return crypto_hash_update(e->data, sg_src, sg_src->length);
}