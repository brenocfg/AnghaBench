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
struct coff_ofile {int nsections; scalar_t__ sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  wr_ob (struct coff_ofile*,scalar_t__) ; 
 int /*<<< orphan*/  wr_rl (struct coff_ofile*,scalar_t__) ; 
 int /*<<< orphan*/  wr_sh (struct coff_ofile*,scalar_t__) ; 

__attribute__((used)) static void
wr_object_body (struct coff_ofile *p)
{
  int i;

  for (i = 1; i < p->nsections; i++)
    {
      wr_sh (p, p->sections + i);
      wr_ob (p, p->sections + i);
      wr_rl (p, p->sections + i);
    }
}