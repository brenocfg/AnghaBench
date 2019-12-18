#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CONST_STRNEQ (char const*,char*) ; 
#define  OPTION_32 132 
#define  OPTION_64 131 
#define  OPTION_DIVIDE 130 
#define  OPTION_MARCH 129 
#define  OPTION_MTUNE 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,...) ; 
 char** bfd_target_list () ; 
 TYPE_1__* cpu_arch ; 
 int /*<<< orphan*/  cpu_arch_isa ; 
 int /*<<< orphan*/  cpu_arch_isa_flags ; 
 int /*<<< orphan*/  cpu_arch_tune ; 
 int /*<<< orphan*/  cpu_arch_tune_flags ; 
 int cpu_arch_tune_set ; 
 char* default_arch ; 
 int /*<<< orphan*/  free (char const**) ; 
 char* i386_comment_chars ; 
 int /*<<< orphan*/  optimize_align_code ; 
 int /*<<< orphan*/  print_version_id () ; 
 int quiet_warnings ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ xmalloc (int /*<<< orphan*/ ) ; 

int
md_parse_option (int c, char *arg)
{
  unsigned int i;

  switch (c)
    {
    case 'n':
      optimize_align_code = 0;
      break;

    case 'q':
      quiet_warnings = 1;
      break;

#if defined (OBJ_ELF) || defined (OBJ_MAYBE_ELF)
      /* -Qy, -Qn: SVR4 arguments controlling whether a .comment section
	 should be emitted or not.  FIXME: Not implemented.  */
    case 'Q':
      break;

      /* -V: SVR4 argument to print version ID.  */
    case 'V':
      print_version_id ();
      break;

      /* -k: Ignore for FreeBSD compatibility.  */
    case 'k':
      break;

    case 's':
      /* -s: On i386 Solaris, this tells the native assembler to use
	 .stab instead of .stab.excl.  We always use .stab anyhow.  */
      break;
#endif
#if defined (OBJ_ELF) || defined (OBJ_MAYBE_ELF) || defined(TE_PEP)
    case OPTION_64:
      {
	const char **list, **l;

	list = bfd_target_list ();
	for (l = list; *l != NULL; l++)
	  if (CONST_STRNEQ (*l, "elf64-x86-64")
	      || strcmp (*l, "coff-x86-64") == 0
	      || strcmp (*l, "pe-x86-64") == 0
	      || strcmp (*l, "pei-x86-64") == 0)
	    {
	      default_arch = "x86_64";
	      break;
	    }
	if (*l == NULL)
	  as_fatal (_("No compiled in support for x86_64"));
	free (list);
      }
      break;
#endif

    case OPTION_32:
      default_arch = "i386";
      break;

    case OPTION_DIVIDE:
#ifdef SVR4_COMMENT_CHARS
      {
	char *n, *t;
	const char *s;

	n = (char *) xmalloc (strlen (i386_comment_chars) + 1);
	t = n;
	for (s = i386_comment_chars; *s != '\0'; s++)
	  if (*s != '/')
	    *t++ = *s;
	*t = '\0';
	i386_comment_chars = n;
      }
#endif
      break;

    case OPTION_MARCH:
      if (*arg == '.')
	as_fatal (_("Invalid -march= option: `%s'"), arg);
      for (i = 0; i < ARRAY_SIZE (cpu_arch); i++)
	{
	  if (strcmp (arg, cpu_arch [i].name) == 0)
	    {
	      cpu_arch_isa = cpu_arch[i].type;
	      cpu_arch_isa_flags = cpu_arch[i].flags;
	      if (!cpu_arch_tune_set)
		{
		  cpu_arch_tune = cpu_arch_isa;
		  cpu_arch_tune_flags = cpu_arch_isa_flags;
		}
	      break;
	    }
	}
      if (i >= ARRAY_SIZE (cpu_arch))
	as_fatal (_("Invalid -march= option: `%s'"), arg);
      break;

    case OPTION_MTUNE:
      if (*arg == '.')
	as_fatal (_("Invalid -mtune= option: `%s'"), arg);
      for (i = 0; i < ARRAY_SIZE (cpu_arch); i++)
	{
	  if (strcmp (arg, cpu_arch [i].name) == 0)
	    {
	      cpu_arch_tune_set = 1;
	      cpu_arch_tune = cpu_arch [i].type;
	      cpu_arch_tune_flags = cpu_arch[i].flags;
	      break;
	    }
	}
      if (i >= ARRAY_SIZE (cpu_arch))
	as_fatal (_("Invalid -mtune= option: `%s'"), arg);
      break;

    default:
      return 0;
    }
  return 1;
}