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
struct coff_ofile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wr_cs () ; 
 int /*<<< orphan*/  wr_debug (struct coff_ofile*) ; 
 int /*<<< orphan*/  wr_hd (struct coff_ofile*) ; 
 int /*<<< orphan*/  wr_object_body (struct coff_ofile*) ; 
 int /*<<< orphan*/  wr_tr () ; 
 int /*<<< orphan*/  wr_unit_info (struct coff_ofile*) ; 

__attribute__((used)) static void
wr_module (struct coff_ofile *p)
{
  wr_cs ();
  wr_hd (p);
  wr_unit_info (p);
  wr_object_body (p);
  wr_debug (p);
  wr_tr ();
}