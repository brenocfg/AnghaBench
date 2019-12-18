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

/* Variables and functions */
 int /*<<< orphan*/  EF_PPC_EMB ; 
 int /*<<< orphan*/  EF_PPC_RELOCATABLE ; 
 int /*<<< orphan*/  EF_PPC_RELOCATABLE_LIB ; 
 void* FALSE ; 
 int /*<<< orphan*/  SHLIB_MRELOCATABLE ; 
 int /*<<< orphan*/  SHLIB_PIC ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,char*) ; 
 void* msolaris ; 
 int /*<<< orphan*/  parse_cpu (char*) ; 
 int /*<<< orphan*/  ppc_comment_chars ; 
 int /*<<< orphan*/  ppc_eabi_comment_chars ; 
 int /*<<< orphan*/  ppc_flags ; 
 int ppc_obj64 ; 
 int /*<<< orphan*/  ppc_solaris_comment_chars ; 
 int /*<<< orphan*/  print_version_id () ; 
 void* reg_names_p ; 
 int set_target_endian ; 
 int /*<<< orphan*/  shlib ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int target_big_endian ; 

int
md_parse_option (int c, char *arg)
{
  switch (c)
    {
    case 'u':
      /* -u means that any undefined symbols should be treated as
	 external, which is the default for gas anyhow.  */
      break;

#ifdef OBJ_ELF
    case 'l':
      /* Solaris as takes -le (presumably for little endian).  For completeness
	 sake, recognize -be also.  */
      if (strcmp (arg, "e") == 0)
	{
	  target_big_endian = 0;
	  set_target_endian = 1;
	}
      else
	return 0;

      break;

    case 'b':
      if (strcmp (arg, "e") == 0)
	{
	  target_big_endian = 1;
	  set_target_endian = 1;
	}
      else
	return 0;

      break;

    case 'K':
      /* Recognize -K PIC.  */
      if (strcmp (arg, "PIC") == 0 || strcmp (arg, "pic") == 0)
	{
	  shlib = SHLIB_PIC;
	  ppc_flags |= EF_PPC_RELOCATABLE_LIB;
	}
      else
	return 0;

      break;
#endif

      /* a64 and a32 determine whether to use XCOFF64 or XCOFF32.  */
    case 'a':
      if (strcmp (arg, "64") == 0)
	{
#ifdef BFD64
	  ppc_obj64 = 1;
#else
	  as_fatal (_("%s unsupported"), "-a64");
#endif
	}
      else if (strcmp (arg, "32") == 0)
	ppc_obj64 = 0;
      else
	return 0;
      break;

    case 'm':
      if (parse_cpu (arg))
	;

      else if (strcmp (arg, "regnames") == 0)
	reg_names_p = TRUE;

      else if (strcmp (arg, "no-regnames") == 0)
	reg_names_p = FALSE;

#ifdef OBJ_ELF
      /* -mrelocatable/-mrelocatable-lib -- warn about initializations
	 that require relocation.  */
      else if (strcmp (arg, "relocatable") == 0)
	{
	  shlib = SHLIB_MRELOCATABLE;
	  ppc_flags |= EF_PPC_RELOCATABLE;
	}

      else if (strcmp (arg, "relocatable-lib") == 0)
	{
	  shlib = SHLIB_MRELOCATABLE;
	  ppc_flags |= EF_PPC_RELOCATABLE_LIB;
	}

      /* -memb, set embedded bit.  */
      else if (strcmp (arg, "emb") == 0)
	ppc_flags |= EF_PPC_EMB;

      /* -mlittle/-mbig set the endianess.  */
      else if (strcmp (arg, "little") == 0
	       || strcmp (arg, "little-endian") == 0)
	{
	  target_big_endian = 0;
	  set_target_endian = 1;
	}

      else if (strcmp (arg, "big") == 0 || strcmp (arg, "big-endian") == 0)
	{
	  target_big_endian = 1;
	  set_target_endian = 1;
	}

      else if (strcmp (arg, "solaris") == 0)
	{
	  msolaris = TRUE;
	  ppc_comment_chars = ppc_solaris_comment_chars;
	}

      else if (strcmp (arg, "no-solaris") == 0)
	{
	  msolaris = FALSE;
	  ppc_comment_chars = ppc_eabi_comment_chars;
	}
#endif
      else
	{
	  as_bad (_("invalid switch -m%s"), arg);
	  return 0;
	}
      break;

#ifdef OBJ_ELF
      /* -V: SVR4 argument to print version ID.  */
    case 'V':
      print_version_id ();
      break;

      /* -Qy, -Qn: SVR4 arguments controlling whether a .comment section
	 should be emitted or not.  FIXME: Not implemented.  */
    case 'Q':
      break;

      /* Solaris takes -s to specify that .stabs go in a .stabs section,
	 rather than .stabs.excl, which is ignored by the linker.
	 FIXME: Not implemented.  */
    case 's':
      if (arg)
	return 0;

      break;
#endif

    default:
      return 0;
    }

  return 1;
}