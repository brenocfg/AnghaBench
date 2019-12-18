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
struct ivopts_data {int /*<<< orphan*/  iv_candidates; } ;

/* Variables and functions */
 int VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_cand_p ; 

__attribute__((used)) static inline unsigned
n_iv_cands (struct ivopts_data *data)
{
  return VEC_length (iv_cand_p, data->iv_candidates);
}