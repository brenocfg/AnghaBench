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
struct ivopts_data {int dummy; } ;
struct iv_ca {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iv_ca_free (struct iv_ca**) ; 
 struct iv_ca* iv_ca_new (struct ivopts_data*) ; 
 int /*<<< orphan*/  iv_use (struct ivopts_data*,unsigned int) ; 
 unsigned int n_iv_uses (struct ivopts_data*) ; 
 int /*<<< orphan*/  try_add_cand_for (struct ivopts_data*,struct iv_ca*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iv_ca *
get_initial_solution (struct ivopts_data *data)
{
  struct iv_ca *ivs = iv_ca_new (data);
  unsigned i;

  for (i = 0; i < n_iv_uses (data); i++)
    if (!try_add_cand_for (data, ivs, iv_use (data, i)))
      {
	iv_ca_free (&ivs);
	return NULL;
      }

  return ivs;
}