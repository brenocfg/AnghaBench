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
struct rtx_iv {int dummy; } ;
struct df_ref {int dummy; } ;

/* Variables and functions */
 struct df_ref* DF_DEFS_GET (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int DF_DEFS_SIZE (int /*<<< orphan*/ ) ; 
 struct rtx_iv* DF_REF_IV (struct df_ref*) ; 
 int /*<<< orphan*/  DF_REF_IV_SET (struct df_ref*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bivs ; 
 int /*<<< orphan*/  df ; 
 int /*<<< orphan*/  free (struct rtx_iv*) ; 
 int /*<<< orphan*/  htab_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clear_iv_info (void)
{
  unsigned i, n_defs = DF_DEFS_SIZE (df);
  struct rtx_iv *iv;
  struct df_ref *def;

  for (i = 0; i < n_defs; i++)
    {
      def = DF_DEFS_GET (df, i);
      iv = DF_REF_IV (def);
      if (!iv)
	continue;
      free (iv);
      DF_REF_IV_SET (def, NULL);
    }

  htab_empty (bivs);
}