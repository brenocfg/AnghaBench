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
struct ivopts_data {int consider_all_candidates; int /*<<< orphan*/  important_candidates; } ;
struct iv_use {int /*<<< orphan*/  related_cands; } ;
struct iv_cand {scalar_t__ important; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 unsigned int CONSIDER_ALL_CANDIDATES_BOUND ; 
 int /*<<< orphan*/  bitmap_ior_into (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,unsigned int) ; 
 struct iv_cand* iv_cand (struct ivopts_data*,unsigned int) ; 
 struct iv_use* iv_use (struct ivopts_data*,unsigned int) ; 
 unsigned int n_iv_cands (struct ivopts_data*) ; 
 unsigned int n_iv_uses (struct ivopts_data*) ; 

__attribute__((used)) static void
record_important_candidates (struct ivopts_data *data)
{
  unsigned i;
  struct iv_use *use;

  for (i = 0; i < n_iv_cands (data); i++)
    {
      struct iv_cand *cand = iv_cand (data, i);

      if (cand->important)
	bitmap_set_bit (data->important_candidates, i);
    }

  data->consider_all_candidates = (n_iv_cands (data)
				   <= CONSIDER_ALL_CANDIDATES_BOUND);

  if (data->consider_all_candidates)
    {
      /* We will not need "related_cands" bitmaps in this case,
	 so release them to decrease peak memory consumption.  */
      for (i = 0; i < n_iv_uses (data); i++)
	{
	  use = iv_use (data, i);
	  BITMAP_FREE (use->related_cands);
	}
    }
  else
    {
      /* Add important candidates to the related_cands bitmaps.  */
      for (i = 0; i < n_iv_uses (data); i++)
	bitmap_ior_into (iv_use (data, i)->related_cands,
			 data->important_candidates);
    }
}