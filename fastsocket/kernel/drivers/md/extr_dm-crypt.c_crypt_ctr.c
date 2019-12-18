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
typedef  int /*<<< orphan*/  u8 ;
struct dm_target {char* error; int num_flush_requests; int /*<<< orphan*/  table; struct crypt_config* private; } ;
struct dm_crypt_request {int dummy; } ;
struct crypt_config {unsigned int key_size; int dmreq_start; unsigned long long iv_offset; unsigned long long start; void* crypt_queue; void* io_queue; int /*<<< orphan*/  dev; int /*<<< orphan*/  bs; int /*<<< orphan*/  page_pool; int /*<<< orphan*/ * req; int /*<<< orphan*/  req_pool; scalar_t__ iv_size; int /*<<< orphan*/  tfm; int /*<<< orphan*/  io_pool; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MIN_IOS ; 
 int /*<<< orphan*/  MIN_POOL_PAGES ; 
 int /*<<< orphan*/  _crypt_io_pool ; 
 int /*<<< orphan*/  bioset_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* create_singlethread_workqueue (char*) ; 
 int crypt_ctr_cipher (struct dm_target*,char*,char*) ; 
 int /*<<< orphan*/  crypt_dtr (struct dm_target*) ; 
 int crypto_ablkcipher_alignmask (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ablkcipher_reqsize (int /*<<< orphan*/ ) ; 
 int crypto_tfm_ctx_alignment () ; 
 scalar_t__ dm_get_device (struct dm_target*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 
 struct crypt_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_create_kmalloc_pool (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mempool_create_page_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_create_slab_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,unsigned long long*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int crypt_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	struct crypt_config *cc;
	unsigned int key_size;
	unsigned long long tmpll;
	int ret;

	if (argc != 5) {
		ti->error = "Not enough arguments";
		return -EINVAL;
	}

	key_size = strlen(argv[1]) >> 1;

	cc = kzalloc(sizeof(*cc) + key_size * sizeof(u8), GFP_KERNEL);
	if (!cc) {
		ti->error = "Cannot allocate encryption context";
		return -ENOMEM;
	}
	cc->key_size = key_size;

	ti->private = cc;
	ret = crypt_ctr_cipher(ti, argv[0], argv[1]);
	if (ret < 0)
		goto bad;

	ret = -ENOMEM;
	cc->io_pool = mempool_create_slab_pool(MIN_IOS, _crypt_io_pool);
	if (!cc->io_pool) {
		ti->error = "Cannot allocate crypt io mempool";
		goto bad;
	}

	cc->dmreq_start = sizeof(struct ablkcipher_request);
	cc->dmreq_start += crypto_ablkcipher_reqsize(cc->tfm);
	cc->dmreq_start = ALIGN(cc->dmreq_start, crypto_tfm_ctx_alignment());
	cc->dmreq_start += crypto_ablkcipher_alignmask(cc->tfm) &
			   ~(crypto_tfm_ctx_alignment() - 1);

	cc->req_pool = mempool_create_kmalloc_pool(MIN_IOS, cc->dmreq_start +
			sizeof(struct dm_crypt_request) + cc->iv_size);
	if (!cc->req_pool) {
		ti->error = "Cannot allocate crypt request mempool";
		goto bad;
	}
	cc->req = NULL;

	cc->page_pool = mempool_create_page_pool(MIN_POOL_PAGES, 0);
	if (!cc->page_pool) {
		ti->error = "Cannot allocate page mempool";
		goto bad;
	}

	cc->bs = bioset_create(MIN_IOS, 0);
	if (!cc->bs) {
		ti->error = "Cannot allocate crypt bioset";
		goto bad;
	}

	ret = -EINVAL;
	if (sscanf(argv[2], "%llu", &tmpll) != 1) {
		ti->error = "Invalid iv_offset sector";
		goto bad;
	}
	cc->iv_offset = tmpll;

	if (dm_get_device(ti, argv[3], dm_table_get_mode(ti->table), &cc->dev)) {
		ti->error = "Device lookup failed";
		goto bad;
	}

	if (sscanf(argv[4], "%llu", &tmpll) != 1) {
		ti->error = "Invalid device sector";
		goto bad;
	}
	cc->start = tmpll;

	ret = -ENOMEM;
	cc->io_queue = create_singlethread_workqueue("kcryptd_io");
	if (!cc->io_queue) {
		ti->error = "Couldn't create kcryptd io queue";
		goto bad;
	}

	cc->crypt_queue = create_singlethread_workqueue("kcryptd");
	if (!cc->crypt_queue) {
		ti->error = "Couldn't create kcryptd queue";
		goto bad;
	}

	ti->num_flush_requests = 1;
	return 0;

bad:
	crypt_dtr(ti);
	return ret;
}