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
struct scatterlist {int dummy; } ;
struct hash_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_hash (int /*<<< orphan*/ ) ; 
 int crypto_hash_final (struct hash_desc*,char*) ; 
 int crypto_hash_update (struct hash_desc*,struct scatterlist*,int) ; 
 int init_desc (struct hash_desc*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void*,int) ; 

int ima_calc_template_hash(int template_len, void *template, char *digest)
{
	struct hash_desc desc;
	struct scatterlist sg[1];
	int rc;

	rc = init_desc(&desc);
	if (rc != 0)
		return rc;

	sg_init_one(sg, template, template_len);
	rc = crypto_hash_update(&desc, sg, template_len);
	if (!rc)
		rc = crypto_hash_final(&desc, digest);
	crypto_free_hash(desc.tfm);
	return rc;
}