#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cie_info {int code_alignment; int z_augmentation; } ;
struct TYPE_6__ {int fr_fix; char* fr_literal; struct TYPE_6__* fr_next; } ;
typedef  TYPE_2__ fragS ;
struct TYPE_7__ {int fx_where; scalar_t__ fx_size; struct TYPE_7__* fx_next; TYPE_2__* fx_frag; } ;
typedef  TYPE_3__ fixS ;
struct TYPE_8__ {TYPE_1__* frchainP; } ;
struct TYPE_5__ {TYPE_3__* fix_root; TYPE_2__* frch_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  now_seg ; 
 TYPE_4__* seg_info (int /*<<< orphan*/ ) ; 
 char* segment_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
get_cie_info (struct cie_info *info)
{
  fragS *f;
  fixS *fix;
  int offset;
  char CIE_id;
  char augmentation[10];
  int iaug;
  int code_alignment = 0;

  /* We should find the CIE at the start of the section.  */

  f = seg_info (now_seg)->frchainP->frch_root;
  fix = seg_info (now_seg)->frchainP->fix_root;

  /* Look through the frags of the section to find the code alignment.  */

  /* First make sure that the CIE Identifier Tag is 0/-1.  */

  if (strcmp (segment_name (now_seg), ".debug_frame") == 0)
    CIE_id = (char)0xff;
  else
    CIE_id = 0;

  offset = 4;
  while (f != NULL && offset >= f->fr_fix)
    {
      offset -= f->fr_fix;
      f = f->fr_next;
    }
  if (f == NULL
      || f->fr_fix - offset < 4
      || f->fr_literal[offset] != CIE_id
      || f->fr_literal[offset + 1] != CIE_id
      || f->fr_literal[offset + 2] != CIE_id
      || f->fr_literal[offset + 3] != CIE_id)
    return 0;

  /* Next make sure the CIE version number is 1.  */

  offset += 4;
  while (f != NULL && offset >= f->fr_fix)
    {
      offset -= f->fr_fix;
      f = f->fr_next;
    }
  if (f == NULL
      || f->fr_fix - offset < 1
      || f->fr_literal[offset] != 1)
    return 0;

  /* Skip the augmentation (a null terminated string).  */

  iaug = 0;
  ++offset;
  while (1)
    {
      while (f != NULL && offset >= f->fr_fix)
	{
	  offset -= f->fr_fix;
	  f = f->fr_next;
	}
      if (f == NULL)
	return 0;

      while (offset < f->fr_fix && f->fr_literal[offset] != '\0')
	{
	  if ((size_t) iaug < (sizeof augmentation) - 1)
	    {
	      augmentation[iaug] = f->fr_literal[offset];
	      ++iaug;
	    }
	  ++offset;
	}
      if (offset < f->fr_fix)
	break;
    }
  ++offset;
  while (f != NULL && offset >= f->fr_fix)
    {
      offset -= f->fr_fix;
      f = f->fr_next;
    }
  if (f == NULL)
    return 0;

  augmentation[iaug] = '\0';
  if (augmentation[0] == '\0')
    {
      /* No augmentation.  */
    }
  else if (strcmp (augmentation, "eh") == 0)
    {
      /* We have to skip a pointer.  Unfortunately, we don't know how
	 large it is.  We find out by looking for a matching fixup.  */
      while (fix != NULL
	     && (fix->fx_frag != f || fix->fx_where != offset))
	fix = fix->fx_next;
      if (fix == NULL)
	offset += 4;
      else
	offset += fix->fx_size;
      while (f != NULL && offset >= f->fr_fix)
	{
	  offset -= f->fr_fix;
	  f = f->fr_next;
	}
      if (f == NULL)
	return 0;
    }
  else if (augmentation[0] != 'z')
    return 0;

  /* We're now at the code alignment factor, which is a ULEB128.  If
     it isn't a single byte, forget it.  */

  code_alignment = f->fr_literal[offset] & 0xff;
  if ((code_alignment & 0x80) != 0)
    code_alignment = 0;

  info->code_alignment = code_alignment;
  info->z_augmentation = (augmentation[0] == 'z');

  return 1;
}