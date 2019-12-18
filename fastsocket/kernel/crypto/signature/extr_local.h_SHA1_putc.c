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
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_shash_update (struct shash_desc*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void SHA1_putc(struct shash_desc *digest, uint8_t ch)
{
	crypto_shash_update(digest, &ch, 1);
}