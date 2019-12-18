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
struct iv_use {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dump_use (int /*<<< orphan*/ *,struct iv_use*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 struct iv_use* iv_use (struct ivopts_data*,unsigned int) ; 
 unsigned int n_iv_uses (struct ivopts_data*) ; 

void
dump_uses (FILE *file, struct ivopts_data *data)
{
  unsigned i;
  struct iv_use *use;

  for (i = 0; i < n_iv_uses (data); i++)
    {
      use = iv_use (data, i);

      dump_use (file, use);
      fprintf (file, "\n");
    }
}