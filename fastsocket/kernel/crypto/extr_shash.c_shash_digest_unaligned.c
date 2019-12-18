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
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int crypto_shash_finup (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_shash_init (struct shash_desc*) ; 

__attribute__((used)) static int shash_digest_unaligned(struct shash_desc *desc, const u8 *data,
				  unsigned int len, u8 *out)
{
	return crypto_shash_init(desc) ?:
	       crypto_shash_finup(desc, data, len, out);
}