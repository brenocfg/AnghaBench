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
struct TYPE_4__ {scalar_t__ sltdesc; int /*<<< orphan*/  address; } ;
struct TYPE_3__ {int /*<<< orphan*/  address; } ;
union sltentry {TYPE_2__ snorm; TYPE_1__ snormoff; } ;
struct objfile {int dummy; } ;
typedef  scalar_t__ sltpointer ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ SLT_END ; 
 scalar_t__ SLT_EXIT ; 
 scalar_t__ SLT_NORMAL ; 
 scalar_t__ SLT_NORMAL_OFFSET ; 
 union sltentry* hpread_get_slt (scalar_t__,struct objfile*) ; 

__attribute__((used)) static CORE_ADDR
hpread_get_location (sltpointer index, struct objfile *objfile)
{
  union sltentry *sl_bufp;
  int i;

  /* code location of special sltentrys is determined from context */
  sl_bufp = hpread_get_slt (index, objfile);

  if (sl_bufp->snorm.sltdesc == SLT_END)
    {
      /* find previous normal sltentry and get address */
      for (i = 0; ((sl_bufp->snorm.sltdesc != SLT_NORMAL) &&
		   (sl_bufp->snorm.sltdesc != SLT_NORMAL_OFFSET) &&
		   (sl_bufp->snorm.sltdesc != SLT_EXIT)); i++)
	sl_bufp = hpread_get_slt (index - i, objfile);
      if (sl_bufp->snorm.sltdesc == SLT_NORMAL_OFFSET)
	return sl_bufp->snormoff.address;
      else
	return sl_bufp->snorm.address;
    }

  /* find next normal sltentry and get address */
  for (i = 0; ((sl_bufp->snorm.sltdesc != SLT_NORMAL) &&
	       (sl_bufp->snorm.sltdesc != SLT_NORMAL_OFFSET) &&
	       (sl_bufp->snorm.sltdesc != SLT_EXIT)); i++)
    sl_bufp = hpread_get_slt (index + i, objfile);
  if (sl_bufp->snorm.sltdesc == SLT_NORMAL_OFFSET)
    return sl_bufp->snormoff.address;
  else
    return sl_bufp->snorm.address;
}