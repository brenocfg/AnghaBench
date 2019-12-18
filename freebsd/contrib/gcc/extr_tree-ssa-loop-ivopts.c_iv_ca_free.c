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
struct iv_ca {struct iv_ca* n_invariant_uses; int /*<<< orphan*/  cands; struct iv_ca* n_cand_uses; struct iv_ca* cand_for_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct iv_ca*) ; 

__attribute__((used)) static void
iv_ca_free (struct iv_ca **ivs)
{
  free ((*ivs)->cand_for_use);
  free ((*ivs)->n_cand_uses);
  BITMAP_FREE ((*ivs)->cands);
  free ((*ivs)->n_invariant_uses);
  free (*ivs);
  *ivs = NULL;
}