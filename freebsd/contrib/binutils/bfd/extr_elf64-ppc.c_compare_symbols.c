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
struct TYPE_3__ {int flags; scalar_t__ value; TYPE_2__* section; } ;
typedef  TYPE_1__ asymbol ;
struct TYPE_4__ {int flags; scalar_t__ id; scalar_t__ vma; } ;

/* Variables and functions */
 int BSF_DYNAMIC ; 
 int BSF_FUNCTION ; 
 int BSF_GLOBAL ; 
 int BSF_SECTION_SYM ; 
 int BSF_WEAK ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_THREAD_LOCAL ; 
 TYPE_2__* synthetic_opd ; 
 scalar_t__ synthetic_relocatable ; 

__attribute__((used)) static int
compare_symbols (const void *ap, const void *bp)
{
  const asymbol *a = * (const asymbol **) ap;
  const asymbol *b = * (const asymbol **) bp;

  /* Section symbols first.  */
  if ((a->flags & BSF_SECTION_SYM) && !(b->flags & BSF_SECTION_SYM))
    return -1;
  if (!(a->flags & BSF_SECTION_SYM) && (b->flags & BSF_SECTION_SYM))
    return 1;

  /* then .opd symbols.  */
  if (a->section == synthetic_opd && b->section != synthetic_opd)
    return -1;
  if (a->section != synthetic_opd && b->section == synthetic_opd)
    return 1;

  /* then other code symbols.  */
  if ((a->section->flags & (SEC_CODE | SEC_ALLOC | SEC_THREAD_LOCAL))
      == (SEC_CODE | SEC_ALLOC)
      && (b->section->flags & (SEC_CODE | SEC_ALLOC | SEC_THREAD_LOCAL))
	 != (SEC_CODE | SEC_ALLOC))
    return -1;

  if ((a->section->flags & (SEC_CODE | SEC_ALLOC | SEC_THREAD_LOCAL))
      != (SEC_CODE | SEC_ALLOC)
      && (b->section->flags & (SEC_CODE | SEC_ALLOC | SEC_THREAD_LOCAL))
	 == (SEC_CODE | SEC_ALLOC))
    return 1;

  if (synthetic_relocatable)
    {
      if (a->section->id < b->section->id)
	return -1;

      if (a->section->id > b->section->id)
	return 1;
    }

  if (a->value + a->section->vma < b->value + b->section->vma)
    return -1;

  if (a->value + a->section->vma > b->value + b->section->vma)
    return 1;

  /* For syms with the same value, prefer strong dynamic global function
     syms over other syms.  */
  if ((a->flags & BSF_GLOBAL) != 0 && (b->flags & BSF_GLOBAL) == 0)
    return -1;

  if ((a->flags & BSF_GLOBAL) == 0 && (b->flags & BSF_GLOBAL) != 0)
    return 1;

  if ((a->flags & BSF_FUNCTION) != 0 && (b->flags & BSF_FUNCTION) == 0)
    return -1;

  if ((a->flags & BSF_FUNCTION) == 0 && (b->flags & BSF_FUNCTION) != 0)
    return 1;

  if ((a->flags & BSF_WEAK) == 0 && (b->flags & BSF_WEAK) != 0)
    return -1;

  if ((a->flags & BSF_WEAK) != 0 && (b->flags & BSF_WEAK) == 0)
    return 1;

  if ((a->flags & BSF_DYNAMIC) != 0 && (b->flags & BSF_DYNAMIC) == 0)
    return -1;

  if ((a->flags & BSF_DYNAMIC) == 0 && (b->flags & BSF_DYNAMIC) != 0)
    return 1;

  return 0;
}