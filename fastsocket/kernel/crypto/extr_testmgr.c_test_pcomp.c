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
struct pcomp_testvec {int inlen; int outlen; int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  paramsize; int /*<<< orphan*/  params; } ;
struct crypto_pcomp {int dummy; } ;
struct comp_request {int avail_in; char* next_out; int avail_out; int /*<<< orphan*/  next_in; } ;
typedef  int /*<<< orphan*/  result ;

/* Variables and functions */
 int COMP_BUF_SIZE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int crypto_compress_final (struct crypto_pcomp*,struct comp_request*) ; 
 int crypto_compress_init (struct crypto_pcomp*) ; 
 int crypto_compress_setup (struct crypto_pcomp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_compress_update (struct crypto_pcomp*,struct comp_request*) ; 
 int crypto_decompress_final (struct crypto_pcomp*,struct comp_request*) ; 
 int crypto_decompress_init (struct crypto_pcomp*) ; 
 int crypto_decompress_setup (struct crypto_pcomp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_decompress_update (struct crypto_pcomp*,struct comp_request*) ; 
 int /*<<< orphan*/  crypto_pcomp_tfm (struct crypto_pcomp*) ; 
 char* crypto_tfm_alg_driver_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexdump (char*,unsigned int) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,char const*,...) ; 

__attribute__((used)) static int test_pcomp(struct crypto_pcomp *tfm,
		      struct pcomp_testvec *ctemplate,
		      struct pcomp_testvec *dtemplate, int ctcount,
		      int dtcount)
{
	const char *algo = crypto_tfm_alg_driver_name(crypto_pcomp_tfm(tfm));
	unsigned int i;
	char result[COMP_BUF_SIZE];
	int res;

	for (i = 0; i < ctcount; i++) {
		struct comp_request req;
		unsigned int produced = 0;

		res = crypto_compress_setup(tfm, ctemplate[i].params,
					    ctemplate[i].paramsize);
		if (res) {
			pr_err("alg: pcomp: compression setup failed on test "
			       "%d for %s: error=%d\n", i + 1, algo, res);
			return res;
		}

		res = crypto_compress_init(tfm);
		if (res) {
			pr_err("alg: pcomp: compression init failed on test "
			       "%d for %s: error=%d\n", i + 1, algo, res);
			return res;
		}

		memset(result, 0, sizeof(result));

		req.next_in = ctemplate[i].input;
		req.avail_in = ctemplate[i].inlen / 2;
		req.next_out = result;
		req.avail_out = ctemplate[i].outlen / 2;

		res = crypto_compress_update(tfm, &req);
		if (res < 0 && (res != -EAGAIN || req.avail_in)) {
			pr_err("alg: pcomp: compression update failed on test "
			       "%d for %s: error=%d\n", i + 1, algo, res);
			return res;
		}
		if (res > 0)
			produced += res;

		/* Add remaining input data */
		req.avail_in += (ctemplate[i].inlen + 1) / 2;

		res = crypto_compress_update(tfm, &req);
		if (res < 0 && (res != -EAGAIN || req.avail_in)) {
			pr_err("alg: pcomp: compression update failed on test "
			       "%d for %s: error=%d\n", i + 1, algo, res);
			return res;
		}
		if (res > 0)
			produced += res;

		/* Provide remaining output space */
		req.avail_out += COMP_BUF_SIZE - ctemplate[i].outlen / 2;

		res = crypto_compress_final(tfm, &req);
		if (res < 0) {
			pr_err("alg: pcomp: compression final failed on test "
			       "%d for %s: error=%d\n", i + 1, algo, res);
			return res;
		}
		produced += res;

		if (COMP_BUF_SIZE - req.avail_out != ctemplate[i].outlen) {
			pr_err("alg: comp: Compression test %d failed for %s: "
			       "output len = %d (expected %d)\n", i + 1, algo,
			       COMP_BUF_SIZE - req.avail_out,
			       ctemplate[i].outlen);
			return -EINVAL;
		}

		if (produced != ctemplate[i].outlen) {
			pr_err("alg: comp: Compression test %d failed for %s: "
			       "returned len = %u (expected %d)\n", i + 1,
			       algo, produced, ctemplate[i].outlen);
			return -EINVAL;
		}

		if (memcmp(result, ctemplate[i].output, ctemplate[i].outlen)) {
			pr_err("alg: pcomp: Compression test %d failed for "
			       "%s\n", i + 1, algo);
			hexdump(result, ctemplate[i].outlen);
			return -EINVAL;
		}
	}

	for (i = 0; i < dtcount; i++) {
		struct comp_request req;
		unsigned int produced = 0;

		res = crypto_decompress_setup(tfm, dtemplate[i].params,
					      dtemplate[i].paramsize);
		if (res) {
			pr_err("alg: pcomp: decompression setup failed on "
			       "test %d for %s: error=%d\n", i + 1, algo, res);
			return res;
		}

		res = crypto_decompress_init(tfm);
		if (res) {
			pr_err("alg: pcomp: decompression init failed on test "
			       "%d for %s: error=%d\n", i + 1, algo, res);
			return res;
		}

		memset(result, 0, sizeof(result));

		req.next_in = dtemplate[i].input;
		req.avail_in = dtemplate[i].inlen / 2;
		req.next_out = result;
		req.avail_out = dtemplate[i].outlen / 2;

		res = crypto_decompress_update(tfm, &req);
		if (res < 0 && (res != -EAGAIN || req.avail_in)) {
			pr_err("alg: pcomp: decompression update failed on "
			       "test %d for %s: error=%d\n", i + 1, algo, res);
			return res;
		}
		if (res > 0)
			produced += res;

		/* Add remaining input data */
		req.avail_in += (dtemplate[i].inlen + 1) / 2;

		res = crypto_decompress_update(tfm, &req);
		if (res < 0 && (res != -EAGAIN || req.avail_in)) {
			pr_err("alg: pcomp: decompression update failed on "
			       "test %d for %s: error=%d\n", i + 1, algo, res);
			return res;
		}
		if (res > 0)
			produced += res;

		/* Provide remaining output space */
		req.avail_out += COMP_BUF_SIZE - dtemplate[i].outlen / 2;

		res = crypto_decompress_final(tfm, &req);
		if (res < 0 && (res != -EAGAIN || req.avail_in)) {
			pr_err("alg: pcomp: decompression final failed on "
			       "test %d for %s: error=%d\n", i + 1, algo, res);
			return res;
		}
		if (res > 0)
			produced += res;

		if (COMP_BUF_SIZE - req.avail_out != dtemplate[i].outlen) {
			pr_err("alg: comp: Decompression test %d failed for "
			       "%s: output len = %d (expected %d)\n", i + 1,
			       algo, COMP_BUF_SIZE - req.avail_out,
			       dtemplate[i].outlen);
			return -EINVAL;
		}

		if (produced != dtemplate[i].outlen) {
			pr_err("alg: comp: Decompression test %d failed for "
			       "%s: returned len = %u (expected %d)\n", i + 1,
			       algo, produced, dtemplate[i].outlen);
			return -EINVAL;
		}

		if (memcmp(result, dtemplate[i].output, dtemplate[i].outlen)) {
			pr_err("alg: pcomp: Decompression test %d failed for "
			       "%s\n", i + 1, algo);
			hexdump(result, dtemplate[i].outlen);
			return -EINVAL;
		}
	}

	return 0;
}