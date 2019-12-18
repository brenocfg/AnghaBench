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
struct sra_elt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_sra_elt_name (int /*<<< orphan*/ ,struct sra_elt*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
debug_sra_elt_name (struct sra_elt *elt)
{
  dump_sra_elt_name (stderr, elt);
  fputc ('\n', stderr);
}