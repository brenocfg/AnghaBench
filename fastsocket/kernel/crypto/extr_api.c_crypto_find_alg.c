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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_type {struct crypto_alg* (* lookup ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  maskset; int /*<<< orphan*/  type; int /*<<< orphan*/  maskclear; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 struct crypto_alg* crypto_alg_mod_lookup (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct crypto_alg *crypto_find_alg(const char *alg_name,
				   const struct crypto_type *frontend,
				   u32 type, u32 mask)
{
	struct crypto_alg *(*lookup)(const char *name, u32 type, u32 mask) =
		crypto_alg_mod_lookup;

	if (frontend) {
		type &= frontend->maskclear;
		mask &= frontend->maskclear;
		type |= frontend->type;
		mask |= frontend->maskset;

		if (frontend->lookup)
			lookup = frontend->lookup;
	}

	return lookup(alg_name, type, mask);
}