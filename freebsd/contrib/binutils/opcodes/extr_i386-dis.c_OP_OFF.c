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
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 int AFLAG ; 
 int PREFIX_CS ; 
 int PREFIX_DS ; 
 int PREFIX_ES ; 
 int PREFIX_FS ; 
 int PREFIX_GS ; 
 int PREFIX_SS ; 
 int SUFFIX_ALWAYS ; 
 scalar_t__ address_mode ; 
 int /*<<< orphan*/  append_seg () ; 
 size_t ds_reg ; 
 size_t es_reg ; 
 int /*<<< orphan*/  get16 () ; 
 int /*<<< orphan*/  get32 () ; 
 int /*<<< orphan*/  intel_operand_size (int,int) ; 
 scalar_t__ intel_syntax ; 
 scalar_t__ mode_64bit ; 
 char** names_seg ; 
 int /*<<< orphan*/  oappend (char*) ; 
 int prefixes ; 
 int /*<<< orphan*/  print_operand_value (char*,int,int /*<<< orphan*/ ) ; 
 char* scratchbuf ; 

__attribute__((used)) static void
OP_OFF (int bytemode, int sizeflag)
{
  bfd_vma off;

  if (intel_syntax && (sizeflag & SUFFIX_ALWAYS))
    intel_operand_size (bytemode, sizeflag);
  append_seg ();

  if ((sizeflag & AFLAG) || address_mode == mode_64bit)
    off = get32 ();
  else
    off = get16 ();

  if (intel_syntax)
    {
      if (!(prefixes & (PREFIX_CS | PREFIX_SS | PREFIX_DS
			| PREFIX_ES | PREFIX_FS | PREFIX_GS)))
	{
	  oappend (names_seg[ds_reg - es_reg]);
	  oappend (":");
	}
    }
  print_operand_value (scratchbuf, 1, off);
  oappend (scratchbuf);
}