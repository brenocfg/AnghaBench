#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  sadb_alg_id; } ;
struct xfrm_algo_desc {int /*<<< orphan*/  name; TYPE_1__ desc; } ;
struct xfrm_algo_aead {int /*<<< orphan*/  alg_name; int /*<<< orphan*/  alg_icv_len; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  aead_len (struct xfrm_algo_aead*) ; 
 struct xfrm_algo_aead* kmemdup (struct xfrm_algo_aead*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfrm_algo_aead* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfrm_algo_desc* xfrm_aead_get_byname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int attach_aead(struct xfrm_algo_aead **algpp, u8 *props,
		       struct nlattr *rta)
{
	struct xfrm_algo_aead *p, *ualg;
	struct xfrm_algo_desc *algo;

	if (!rta)
		return 0;

	ualg = nla_data(rta);

	algo = xfrm_aead_get_byname(ualg->alg_name, ualg->alg_icv_len, 1);
	if (!algo)
		return -ENOSYS;
	*props = algo->desc.sadb_alg_id;

	p = kmemdup(ualg, aead_len(ualg), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	strcpy(p->alg_name, algo->name);
	*algpp = p;
	return 0;
}