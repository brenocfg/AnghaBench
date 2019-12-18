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
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 struct crypto_alg* __crypto_alg_lookup (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alg_sem ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct crypto_alg *crypto_alg_lookup(const char *name, u32 type, u32 mask)
{
	struct crypto_alg *alg;

	down_read(&crypto_alg_sem);
	alg = __crypto_alg_lookup(name, type, mask);
	up_read(&crypto_alg_sem);

	return alg;
}