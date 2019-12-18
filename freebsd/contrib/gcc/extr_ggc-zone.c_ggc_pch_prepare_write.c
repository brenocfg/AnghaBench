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
struct ggc_pch_data {int /*<<< orphan*/  start_offset; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 

void
ggc_pch_prepare_write (struct ggc_pch_data *d,
		       FILE *f)
{
  /* We seek around a lot while writing.  Record where the end
     of the padding in the PCH file is, so that we can
     locate each object's offset.  */
  d->start_offset = ftell (f);
}