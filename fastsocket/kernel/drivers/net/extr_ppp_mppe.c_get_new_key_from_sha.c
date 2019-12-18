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
struct scatterlist {int dummy; } ;
struct ppp_mppe_state {int keylen; int /*<<< orphan*/  sha1_digest; int /*<<< orphan*/  sha1; int /*<<< orphan*/  session_key; int /*<<< orphan*/  master_key; } ;
struct hash_desc {scalar_t__ flags; int /*<<< orphan*/  tfm; } ;
struct TYPE_2__ {int /*<<< orphan*/  sha_pad2; int /*<<< orphan*/  sha_pad1; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_digest (struct hash_desc*,struct scatterlist*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int setup_sg (struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 TYPE_1__* sha_pad ; 

__attribute__((used)) static void get_new_key_from_sha(struct ppp_mppe_state * state)
{
	struct hash_desc desc;
	struct scatterlist sg[4];
	unsigned int nbytes;

	sg_init_table(sg, 4);

	nbytes = setup_sg(&sg[0], state->master_key, state->keylen);
	nbytes += setup_sg(&sg[1], sha_pad->sha_pad1,
			   sizeof(sha_pad->sha_pad1));
	nbytes += setup_sg(&sg[2], state->session_key, state->keylen);
	nbytes += setup_sg(&sg[3], sha_pad->sha_pad2,
			   sizeof(sha_pad->sha_pad2));

	desc.tfm = state->sha1;
	desc.flags = 0;

	crypto_hash_digest(&desc, sg, nbytes, state->sha1_digest);
}