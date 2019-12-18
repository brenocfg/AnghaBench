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
struct TYPE_3__ {TYPE_2__* types; } ;
struct ieee_info {TYPE_1__ types; } ;
typedef  int /*<<< orphan*/ * debug_type ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_4__ {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ieee_alloc_type (struct ieee_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ieee_builtin_type (struct ieee_info*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ieee_read_number (struct ieee_info*,int /*<<< orphan*/  const**,int*) ; 

__attribute__((used)) static bfd_boolean
ieee_read_type_index (struct ieee_info *info, const bfd_byte **pp,
		      debug_type *ptype)
{
  const bfd_byte *start;
  bfd_vma indx;

  start = *pp;

  if (! ieee_read_number (info, pp, &indx))
    return FALSE;

  if (indx < 256)
    {
      *ptype = ieee_builtin_type (info, start, indx);
      if (*ptype == NULL)
	return FALSE;
      return TRUE;
    }

  indx -= 256;
  if (! ieee_alloc_type (info, indx, TRUE))
    return FALSE;

  *ptype = info->types.types[indx].type;

  return TRUE;
}