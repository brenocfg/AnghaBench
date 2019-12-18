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
struct ggc_pch_data {int /*<<< orphan*/  d; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  free (struct ggc_pch_data*) ; 
 int fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

void
ggc_pch_finish (struct ggc_pch_data *d, FILE *f)
{
  if (fwrite (&d->d, sizeof (d->d), 1, f) != 1)
    fatal_error ("can't write PCH file: %m");
  free (d);
}