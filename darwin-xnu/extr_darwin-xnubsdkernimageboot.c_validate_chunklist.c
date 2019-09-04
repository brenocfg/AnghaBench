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
typedef  int /*<<< orphan*/  uint8_t ;
struct chunklist_sig {int dummy; } ;
struct chunklist_pubkey {int isprod; int /*<<< orphan*/  key; } ;
struct chunklist_hdr {scalar_t__ cl_magic; scalar_t__ cl_file_ver; scalar_t__ cl_chunk_method; scalar_t__ cl_sig_method; int cl_chunk_offset; int cl_sig_offset; int /*<<< orphan*/  cl_chunk_count; } ;
struct chunklist_chunk {int dummy; } ;
typedef  int /*<<< orphan*/  SHA256_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHDBG (char*,...) ; 
 int /*<<< orphan*/  AUTHPRNT (char*,...) ; 
 scalar_t__ CHUNKLIST_FILE_VERSION_10 ; 
 scalar_t__ CHUNKLIST_MAGIC ; 
 size_t CHUNKLIST_NPUBKEYS ; 
 int /*<<< orphan*/  CHUNKLIST_PUBKEY_LEN ; 
 scalar_t__ CHUNKLIST_SIGNATURE_METHOD_10 ; 
 size_t CHUNKLIST_SIG_LEN ; 
 int EINVAL ; 
 int INVALID_SIG ; 
 int MISSING_SIG ; 
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA256_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,void*,size_t) ; 
 struct chunklist_pubkey* chunklist_pubkeys ; 
 scalar_t__ os_add_overflow (int,int,size_t*) ; 
 scalar_t__ os_mul_and_add_overflow (int /*<<< orphan*/ ,int,int,size_t*) ; 
 scalar_t__ os_sub_overflow (size_t,size_t,size_t*) ; 
 int validate_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
validate_chunklist(void *buf, size_t len)
{
	int err = 0;
	size_t sigsz = 0;
	size_t sig_end = 0;
	size_t chunks_end = 0;
	bool valid_sig = false;
	struct chunklist_hdr *hdr = buf;

	if (len < sizeof(struct chunklist_hdr)) {
		AUTHPRNT("no space for header");
		return EINVAL;
	}

	/* recognized file format? */
	if (hdr->cl_magic != CHUNKLIST_MAGIC ||
			hdr->cl_file_ver != CHUNKLIST_FILE_VERSION_10 ||
			hdr->cl_chunk_method != CHUNKLIST_SIGNATURE_METHOD_10 ||
			hdr->cl_sig_method != CHUNKLIST_SIGNATURE_METHOD_10) {
		AUTHPRNT("unrecognized chunklist format");
		return EINVAL;
	}

	/* does the chunk list fall within the bounds of the buffer? */
	if (os_mul_and_add_overflow(hdr->cl_chunk_count, sizeof(struct chunklist_chunk), hdr->cl_chunk_offset, &chunks_end) ||
			hdr->cl_chunk_offset < sizeof(struct chunklist_hdr) || chunks_end > len) {
		AUTHPRNT("invalid chunk_count (%llu) or chunk_offset (%llu)",
				hdr->cl_chunk_count, hdr->cl_chunk_offset);
		return EINVAL;
	}

	/* does the signature fall within the bounds of the buffer? */
	if (os_add_overflow(hdr->cl_sig_offset, sizeof(struct chunklist_sig), &sig_end) ||
			hdr->cl_sig_offset < sizeof(struct chunklist_hdr) ||
			hdr->cl_sig_offset < chunks_end ||
			hdr->cl_sig_offset > len) {
		AUTHPRNT("invalid signature offset (%llu)", hdr->cl_sig_offset);
		return EINVAL;
	}

	if (sig_end > len || os_sub_overflow(len, hdr->cl_sig_offset, &sigsz) || sigsz != CHUNKLIST_SIG_LEN) {
		/* missing or incorrect signature size */
		return MISSING_SIG;
	}

	AUTHDBG("hashing chunklist");

	/* hash the chunklist (excluding the signature) */
	uint8_t sha_digest[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha_ctx;
	SHA256_Init(&sha_ctx);
	SHA256_Update(&sha_ctx, buf, hdr->cl_sig_offset);
	SHA256_Final(sha_digest, &sha_ctx);

	AUTHDBG("validating chunklist signature against pub keys");
	for (size_t i = 0; i < CHUNKLIST_NPUBKEYS; i++) {
		const struct chunklist_pubkey *key = &chunklist_pubkeys[i];
		err = validate_signature(key->key, CHUNKLIST_PUBKEY_LEN,
				buf + hdr->cl_sig_offset, sigsz, sha_digest);
		if (err == 0) {
			AUTHDBG("validated chunklist signature with key %lu (prod=%d)", i, key->isprod);
			valid_sig = key->isprod;
#if IMAGEBOOT_ALLOW_DEVKEYS
			if (!key->isprod) {
				/* allow dev keys in dev builds only */
				AUTHDBG("*** allowing DEV key: this will fail in customer builds ***");
				valid_sig = true;
			}
#endif
			goto out;
		} else if (err == INVALID_SIG) {
			/* try the next key */
		} else {
			goto out; /* something bad happened */
		}
	}

	/* At this point we tried all the keys: nothing went wrong but none of them
	 * signed our chunklist. */
	AUTHPRNT("signature did not verify against any known public key");

out:
	if (err) {
		return err;
	} else if (valid_sig == true) {
		return 0; /* signed, and everything checked out */
	} else {
		return EINVAL;
	}
}