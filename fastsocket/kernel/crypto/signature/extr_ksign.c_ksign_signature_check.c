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
typedef  int uint8_t ;
typedef  int u32 ;
struct shash_desc {int dummy; } ;
struct ksign_signature {scalar_t__* keyid; scalar_t__ version; scalar_t__ timestamp; int sig_class; int* hashed_data; int /*<<< orphan*/  data; } ;
struct ksign_public_key {scalar_t__ timestamp; int /*<<< orphan*/  pkey; } ;
typedef  int /*<<< orphan*/ * MPI ;

/* Variables and functions */
 int BYTES_PER_MPI_LIMB ; 
 int DIGEST_ALGO_SHA1 ; 
 int DSA_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOKEY ; 
 int ENOMEM ; 
 int PUBKEY_ALGO_DSA ; 
 int SHA1_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA1_putc (struct shash_desc*,int) ; 
 int /*<<< orphan*/  SHA1_write (struct shash_desc*,int*,int) ; 
 int /*<<< orphan*/  crypto_shash_final (struct shash_desc*,int*) ; 
 struct ksign_public_key* ksign_get_public_key (scalar_t__*) ; 
 int /*<<< orphan*/  ksign_put_public_key (struct ksign_public_key*) ; 
 int /*<<< orphan*/ * mpi_alloc (int) ; 
 int /*<<< orphan*/  mpi_free (int /*<<< orphan*/ *) ; 
 int mpi_set_buffer (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int ksign_signature_check(const struct ksign_signature *sig,
				 struct shash_desc *digest)
{
	struct ksign_public_key *pk;
	uint8_t sha1[SHA1_DIGEST_SIZE];
	MPI result = NULL;
	int rc = 0;

	pk = ksign_get_public_key(sig->keyid);
	if (!pk) {
		printk("ksign: module signed with unknown public key\n");
		printk("- signature keyid: %08x%08x ver=%u\n",
		       sig->keyid[0], sig->keyid[1], sig->version);
		return -ENOKEY;
	}

	if (pk->timestamp > sig->timestamp)
		printk("ksign:"
		       " public key is %lu seconds newer than the signature"
		       " [%lx < %lx]\n",
		       pk->timestamp - sig->timestamp,
		       pk->timestamp, sig->timestamp);

	/* complete the digest */
	if (sig->version >= 4)
		SHA1_putc(digest, sig->version);
	SHA1_putc(digest, sig->sig_class);

	if (sig->version < 4) {
		u32 a = sig->timestamp;
		SHA1_putc(digest, (a >> 24) & 0xff);
		SHA1_putc(digest, (a >> 16) & 0xff);
		SHA1_putc(digest, (a >>  8) & 0xff);
		SHA1_putc(digest, (a >>  0) & 0xff);
	}
	else {
		uint8_t buf[6];
		size_t n;
		SHA1_putc(digest, PUBKEY_ALGO_DSA);
		SHA1_putc(digest, DIGEST_ALGO_SHA1);
		if (sig->hashed_data) {
			n = (sig->hashed_data[0] << 8) | sig->hashed_data[1];
			SHA1_write(digest, sig->hashed_data, n + 2);
			n += 6;
		}
		else {
			n = 6;
		}

		/* add some magic */
		buf[0] = sig->version;
		buf[1] = 0xff;
		buf[2] = n >> 24;
		buf[3] = n >> 16;
		buf[4] = n >>  8;
		buf[5] = n;
		SHA1_write(digest, buf, 6);
	}

	crypto_shash_final(digest, sha1);

	rc = -ENOMEM;
	result = mpi_alloc((SHA1_DIGEST_SIZE + BYTES_PER_MPI_LIMB - 1) /
			   BYTES_PER_MPI_LIMB);
	if (!result)
		goto cleanup;

	rc = mpi_set_buffer(result, sha1, SHA1_DIGEST_SIZE, 0);
	if (rc < 0)
		goto cleanup;

	rc = DSA_verify(result, sig->data, pk->pkey);

 cleanup:
	mpi_free(result);
	ksign_put_public_key(pk);

	return rc;
}