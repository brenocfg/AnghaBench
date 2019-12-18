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
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_shash_update (struct shash_desc*,void const*,size_t) ; 

__attribute__((used)) static inline void SHA1_write(struct shash_desc *digest, const void *s, size_t n)
{
	crypto_shash_update(digest, s, n);
}