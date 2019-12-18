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
struct xfrm_algo_aead {int alg_key_len; } ;

/* Variables and functions */

__attribute__((used)) static inline int aead_len(struct xfrm_algo_aead *alg)
{
	return sizeof(*alg) + ((alg->alg_key_len + 7) / 8);
}