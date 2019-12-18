#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* segT ;
typedef  TYPE_1__* elf_linked_to_section ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int SEC_LINK_ONCE ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int SHF_GROUP ; 
 int SPECIAL_SECTION_UNWIND ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  as_bad (char*,char const*) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* elf_group_name (TYPE_1__* const) ; 
 int elf_section_flags (TYPE_1__* const) ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 TYPE_1__* now_seg ; 
 char* segment_name (TYPE_1__* const) ; 
 int /*<<< orphan*/  set_section (char*) ; 
 char** special_linkonce_name ; 
 char** special_section_name ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static void
start_unwind_section (const segT text_seg, int sec_index)
{
  /*
    Use a slightly ugly scheme to derive the unwind section names from
    the text section name:

    text sect.  unwind table sect.
    name:       name:                      comments:
    ----------  -----------------          --------------------------------
    .text       .IA_64.unwind
    .text.foo   .IA_64.unwind.text.foo
    .foo        .IA_64.unwind.foo
    .gnu.linkonce.t.foo
		.gnu.linkonce.ia64unw.foo
    _info       .IA_64.unwind_info         gas issues error message (ditto)
    _infoFOO    .IA_64.unwind_infoFOO      gas issues error message (ditto)

    This mapping is done so that:

	(a) An object file with unwind info only in .text will use
	    unwind section names .IA_64.unwind and .IA_64.unwind_info.
	    This follows the letter of the ABI and also ensures backwards
	    compatibility with older toolchains.

	(b) An object file with unwind info in multiple text sections
	    will use separate unwind sections for each text section.
	    This allows us to properly set the "sh_info" and "sh_link"
	    fields in SHT_IA_64_UNWIND as required by the ABI and also
	    lets GNU ld support programs with multiple segments
	    containing unwind info (as might be the case for certain
	    embedded applications).

	(c) An error is issued if there would be a name clash.
  */

  const char *text_name, *sec_text_name;
  char *sec_name;
  const char *prefix = special_section_name [sec_index];
  const char *suffix;
  size_t prefix_len, suffix_len, sec_name_len;

  sec_text_name = segment_name (text_seg);
  text_name = sec_text_name;
  if (strncmp (text_name, "_info", 5) == 0)
    {
      as_bad ("Illegal section name `%s' (causes unwind section name clash)",
	      text_name);
      ignore_rest_of_line ();
      return;
    }
  if (strcmp (text_name, ".text") == 0)
    text_name = "";

  /* Build the unwind section name by appending the (possibly stripped)
     text section name to the unwind prefix.  */
  suffix = text_name;
  if (strncmp (text_name, ".gnu.linkonce.t.",
	       sizeof (".gnu.linkonce.t.") - 1) == 0)
    {
      prefix = special_linkonce_name [sec_index - SPECIAL_SECTION_UNWIND];
      suffix += sizeof (".gnu.linkonce.t.") - 1;
    }

  prefix_len = strlen (prefix);
  suffix_len = strlen (suffix);
  sec_name_len = prefix_len + suffix_len;
  sec_name = alloca (sec_name_len + 1);
  memcpy (sec_name, prefix, prefix_len);
  memcpy (sec_name + prefix_len, suffix, suffix_len);
  sec_name [sec_name_len] = '\0';

  /* Handle COMDAT group.  */
  if ((text_seg->flags & SEC_LINK_ONCE) != 0
      && (elf_section_flags (text_seg) & SHF_GROUP) != 0)
    {
      char *section;
      size_t len, group_name_len;
      const char *group_name = elf_group_name (text_seg);

      if (group_name == NULL)
	{
	  as_bad ("Group section `%s' has no group signature",
		  sec_text_name);
	  ignore_rest_of_line ();
	  return;
	}
      /* We have to construct a fake section directive. */
      group_name_len = strlen (group_name);
      len = (sec_name_len
	     + 16			/* ,"aG",@progbits,  */
	     + group_name_len		/* ,group_name  */
	     + 7);			/* ,comdat  */

      section = alloca (len + 1);
      memcpy (section, sec_name, sec_name_len);
      memcpy (section + sec_name_len, ",\"aG\",@progbits,", 16);
      memcpy (section + sec_name_len + 16, group_name, group_name_len);
      memcpy (section + len - 7, ",comdat", 7);
      section [len] = '\0';
      set_section (section);
    }
  else
    {
      set_section (sec_name);
      bfd_set_section_flags (stdoutput, now_seg,
			     SEC_LOAD | SEC_ALLOC | SEC_READONLY);
    }

  elf_linked_to_section (now_seg) = text_seg;
}