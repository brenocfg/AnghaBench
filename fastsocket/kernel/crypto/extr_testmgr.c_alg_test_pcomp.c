#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct crypto_pcomp {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  count; int /*<<< orphan*/  vecs; } ;
struct TYPE_8__ {int /*<<< orphan*/  count; int /*<<< orphan*/  vecs; } ;
struct TYPE_6__ {TYPE_1__ decomp; TYPE_4__ comp; } ;
struct TYPE_7__ {TYPE_2__ pcomp; } ;
struct alg_test_desc {TYPE_3__ suite; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_pcomp*) ; 
 int PTR_ERR (struct crypto_pcomp*) ; 
 struct crypto_pcomp* crypto_alloc_pcomp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_pcomp (struct crypto_pcomp*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int) ; 
 int test_pcomp (struct crypto_pcomp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alg_test_pcomp(const struct alg_test_desc *desc, const char *driver,
			  u32 type, u32 mask)
{
	struct crypto_pcomp *tfm;
	int err;

	tfm = crypto_alloc_pcomp(driver, type, mask);
	if (IS_ERR(tfm)) {
		pr_err("alg: pcomp: Failed to load transform for %s: %ld\n",
		       driver, PTR_ERR(tfm));
		return PTR_ERR(tfm);
	}

	err = test_pcomp(tfm, desc->suite.pcomp.comp.vecs,
			 desc->suite.pcomp.decomp.vecs,
			 desc->suite.pcomp.comp.count,
			 desc->suite.pcomp.decomp.count);

	crypto_free_pcomp(tfm);
	return err;
}