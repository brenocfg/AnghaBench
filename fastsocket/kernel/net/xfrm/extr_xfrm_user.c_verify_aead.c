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
struct xfrm_algo_aead {char* alg_name; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int CRYPTO_MAX_ALG_NAME ; 
 int EINVAL ; 
 size_t XFRMA_ALG_AEAD ; 
 scalar_t__ aead_len (struct xfrm_algo_aead*) ; 
 struct xfrm_algo_aead* nla_data (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 

__attribute__((used)) static int verify_aead(struct nlattr **attrs)
{
	struct nlattr *rt = attrs[XFRMA_ALG_AEAD];
	struct xfrm_algo_aead *algp;

	if (!rt)
		return 0;

	algp = nla_data(rt);
	if (nla_len(rt) < aead_len(algp))
		return -EINVAL;

	algp->alg_name[CRYPTO_MAX_ALG_NAME - 1] = '\0';
	return 0;
}