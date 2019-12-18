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
struct netfs_crypto_capabilities {int /*<<< orphan*/  cipher_keysize; void* cipher_strlen; void* hash_strlen; } ;

/* Variables and functions */
 void* __cpu_to_be16 (void*) ; 
 int /*<<< orphan*/  __cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void netfs_convert_crypto_capabilities(struct netfs_crypto_capabilities *cap)
{
	cap->hash_strlen = __cpu_to_be16(cap->hash_strlen);
	cap->cipher_strlen = __cpu_to_be16(cap->cipher_strlen);
	cap->cipher_keysize = __cpu_to_be32(cap->cipher_keysize);
}