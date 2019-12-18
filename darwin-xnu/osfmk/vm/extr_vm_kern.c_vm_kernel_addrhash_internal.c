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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  salt ;
typedef  int /*<<< orphan*/  addr ;
typedef  int /*<<< orphan*/  SHA256_CTX ;

/* Variables and functions */
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA256_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ VM_KERNEL_IS_SLID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
vm_kernel_addrhash_internal(
	vm_offset_t addr,
	vm_offset_t *hash_addr,
	uint64_t salt)
{
	assert(salt != 0);

	if (addr == 0) {
		*hash_addr = 0;
		return;
	}

	if (VM_KERNEL_IS_SLID(addr)) {
		*hash_addr = VM_KERNEL_UNSLIDE(addr);
		return;
	}

	vm_offset_t sha_digest[SHA256_DIGEST_LENGTH/sizeof(vm_offset_t)];
	SHA256_CTX sha_ctx;

	SHA256_Init(&sha_ctx);
	SHA256_Update(&sha_ctx, &salt, sizeof(salt));
	SHA256_Update(&sha_ctx, &addr, sizeof(addr));
	SHA256_Final(sha_digest, &sha_ctx);

	*hash_addr = sha_digest[0];
}