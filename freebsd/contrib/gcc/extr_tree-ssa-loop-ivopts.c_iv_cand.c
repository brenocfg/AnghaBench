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
struct iv_cand {int dummy; } ;

/* Variables and functions */
 struct iv_cand* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  iv_cand_p ; 

__attribute__((used)) static inline struct iv_cand *
iv_cand (struct ivopts_data *data, unsigned i)
{
  return VEC_index (iv_cand_p, data->iv_candidates, i);
}