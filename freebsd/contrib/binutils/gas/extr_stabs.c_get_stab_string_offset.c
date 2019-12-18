#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subsegT ;
typedef  TYPE_2__* segT ;
struct TYPE_9__ {unsigned int stab_string_size; } ;
struct TYPE_11__ {TYPE_1__ stabu; } ;
struct TYPE_10__ {char const* name; } ;

/* Variables and functions */
 int SEC_DEBUGGING ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  SEPARATE_STAB_SECTIONS ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 char* frag_more (unsigned int) ; 
 TYPE_2__* now_seg ; 
 int /*<<< orphan*/  now_subseg ; 
 TYPE_5__* seg_info (TYPE_2__*) ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 unsigned int strlen (char const*) ; 
 TYPE_2__* subseg_new (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subseg_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char const* xstrdup (char const*) ; 

unsigned int
get_stab_string_offset (const char *string, const char *stabstr_secname)
{
  unsigned int length;
  unsigned int retval;
  segT save_seg;
  subsegT save_subseg;
  segT seg;
  char *p;

  if (! SEPARATE_STAB_SECTIONS)
    abort ();

  length = strlen (string);

  save_seg = now_seg;
  save_subseg = now_subseg;

  /* Create the stab string section.  */
  seg = subseg_new (stabstr_secname, 0);

  retval = seg_info (seg)->stabu.stab_string_size;
  if (retval <= 0)
    {
      /* Make sure the first string is empty.  */
      p = frag_more (1);
      *p = 0;
      retval = seg_info (seg)->stabu.stab_string_size = 1;
      bfd_set_section_flags (stdoutput, seg, SEC_READONLY | SEC_DEBUGGING);
      if (seg->name == stabstr_secname)
	seg->name = xstrdup (stabstr_secname);
    }

  if (length > 0)
    {				/* Ordinary case.  */
      p = frag_more (length + 1);
      strcpy (p, string);

      seg_info (seg)->stabu.stab_string_size += length + 1;
    }
  else
    retval = 0;

  subseg_set (save_seg, save_subseg);

  return retval;
}