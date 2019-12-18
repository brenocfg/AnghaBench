#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct shash_desc {int dummy; } ;
struct TYPE_9__ {void* hmacmd5; void* md5; TYPE_5__* sdeschmacmd5; TYPE_3__* sdescmd5; } ;
struct TCP_Server_Info {TYPE_4__ secmech; } ;
struct TYPE_6__ {int flags; void* tfm; } ;
struct TYPE_10__ {TYPE_1__ shash; } ;
struct TYPE_7__ {int flags; void* tfm; } ;
struct TYPE_8__ {TYPE_2__ shash; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  cERROR (int,char*) ; 
 void* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (void*) ; 
 int crypto_shash_descsize (void*) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

int
cifs_crypto_shash_allocate(struct TCP_Server_Info *server)
{
	int rc;
	unsigned int size;

	server->secmech.hmacmd5 = crypto_alloc_shash("hmac(md5)", 0, 0);
	if (IS_ERR(server->secmech.hmacmd5)) {
		cERROR(1, "could not allocate crypto hmacmd5\n");
		return PTR_ERR(server->secmech.hmacmd5);
	}

	server->secmech.md5 = crypto_alloc_shash("md5", 0, 0);
	if (IS_ERR(server->secmech.md5)) {
		cERROR(1, "could not allocate crypto md5\n");
		rc = PTR_ERR(server->secmech.md5);
		goto crypto_allocate_md5_fail;
	}

	size = sizeof(struct shash_desc) +
			crypto_shash_descsize(server->secmech.hmacmd5);
	server->secmech.sdeschmacmd5 = kmalloc(size, GFP_KERNEL);
	if (!server->secmech.sdeschmacmd5) {
		cERROR(1, "cifs_crypto_shash_allocate: can't alloc hmacmd5\n");
		rc = -ENOMEM;
		goto crypto_allocate_hmacmd5_sdesc_fail;
	}
	server->secmech.sdeschmacmd5->shash.tfm = server->secmech.hmacmd5;
	server->secmech.sdeschmacmd5->shash.flags = 0x0;


	size = sizeof(struct shash_desc) +
			crypto_shash_descsize(server->secmech.md5);
	server->secmech.sdescmd5 = kmalloc(size, GFP_KERNEL);
	if (!server->secmech.sdescmd5) {
		cERROR(1, "cifs_crypto_shash_allocate: can't alloc md5\n");
		rc = -ENOMEM;
		goto crypto_allocate_md5_sdesc_fail;
	}
	server->secmech.sdescmd5->shash.tfm = server->secmech.md5;
	server->secmech.sdescmd5->shash.flags = 0x0;

	return 0;

crypto_allocate_md5_sdesc_fail:
	kfree(server->secmech.sdeschmacmd5);

crypto_allocate_hmacmd5_sdesc_fail:
	crypto_free_shash(server->secmech.md5);

crypto_allocate_md5_fail:
	crypto_free_shash(server->secmech.hmacmd5);

	return rc;
}