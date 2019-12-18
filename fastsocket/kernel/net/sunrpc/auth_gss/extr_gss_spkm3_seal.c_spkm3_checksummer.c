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
struct hash_desc {int dummy; } ;

/* Variables and functions */
 int crypto_hash_update (struct hash_desc*,struct scatterlist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spkm3_checksummer(struct scatterlist *sg, void *data)
{
	struct hash_desc *desc = data;

	return crypto_hash_update(desc, sg, sg->length);
}