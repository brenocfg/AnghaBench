#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ address; int /*<<< orphan*/  line; } ;
struct TYPE_4__ {scalar_t__ sltdesc; scalar_t__ address; int /*<<< orphan*/  line; } ;
union sltentry {TYPE_1__ snormoff; TYPE_2__ snorm; } ;
struct subfile {int dummy; } ;
struct objfile {int dummy; } ;
typedef  scalar_t__ sltpointer ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ SLT_EXIT ; 
 scalar_t__ SLT_NORMAL ; 
 scalar_t__ SLT_NORMAL_OFFSET ; 
 union sltentry* hpread_get_slt (scalar_t__,struct objfile*) ; 
 int /*<<< orphan*/  record_line (struct subfile*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static sltpointer
hpread_record_lines (struct subfile *subfile, sltpointer s_idx,
		     sltpointer e_idx, struct objfile *objfile,
		     CORE_ADDR offset)
{
  union sltentry *sl_bufp;

  while (s_idx <= e_idx)
    {
      sl_bufp = hpread_get_slt (s_idx, objfile);
      /* Only record "normal" entries in the SLT.  */
      if (sl_bufp->snorm.sltdesc == SLT_NORMAL
	  || sl_bufp->snorm.sltdesc == SLT_EXIT)
	record_line (subfile, sl_bufp->snorm.line,
		     sl_bufp->snorm.address + offset);
      else if (sl_bufp->snorm.sltdesc == SLT_NORMAL_OFFSET)
	record_line (subfile, sl_bufp->snormoff.line,
		     sl_bufp->snormoff.address + offset);
      s_idx++;
    }
  return e_idx;
}