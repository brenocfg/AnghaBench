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
struct ivopts_data {unsigned int max_inv_id; } ;
struct iv_ca {scalar_t__* n_invariant_uses; int /*<<< orphan*/  cands; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int iv_ca_cost (struct iv_ca*) ; 

__attribute__((used)) static void
iv_ca_dump (struct ivopts_data *data, FILE *file, struct iv_ca *ivs)
{
  const char *pref = "  invariants ";
  unsigned i;

  fprintf (file, "  cost %d\n", iv_ca_cost (ivs));
  bitmap_print (file, ivs->cands, "  candidates ","\n");

  for (i = 1; i <= data->max_inv_id; i++)
    if (ivs->n_invariant_uses[i])
      {
	fprintf (file, "%s%d", pref, i);
	pref = ", ";
      }
  fprintf (file, "\n");
}