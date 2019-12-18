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
struct cpu_type {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  OPTION_32ADDR 131 
#define  OPTION_MDEBUG 130 
#define  OPTION_NO_MDEBUG 129 
#define  OPTION_RELAX 128 
 int /*<<< orphan*/  _ (char*) ; 
 int alpha_addr32_on ; 
 int alpha_debug ; 
 int alpha_flag_hash_long_names ; 
 int alpha_flag_mdebug ; 
 int alpha_flag_relax ; 
 int alpha_flag_show_after_trunc ; 
 int alpha_nofloats_on ; 
 int /*<<< orphan*/  alpha_target ; 
 int /*<<< orphan*/  alpha_target_name ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 struct cpu_type* cpu_types ; 
 int /*<<< orphan*/  g_switch_value ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

int
md_parse_option (int c, char *arg)
{
  switch (c)
    {
    case 'F':
      alpha_nofloats_on = 1;
      break;

    case OPTION_32ADDR:
      alpha_addr32_on = 1;
      break;

    case 'g':
      alpha_debug = 1;
      break;

    case 'G':
      g_switch_value = atoi (arg);
      break;

    case 'm':
      {
	const struct cpu_type *p;

	for (p = cpu_types; p->name; ++p)
	  if (strcmp (arg, p->name) == 0)
	    {
	      alpha_target_name = p->name, alpha_target = p->flags;
	      goto found;
	    }
	as_warn (_("Unknown CPU identifier `%s'"), arg);
      found:;
      }
      break;

#ifdef OBJ_EVAX
    case '+':			/* For g++.  Hash any name > 63 chars long.  */
      alpha_flag_hash_long_names = 1;
      break;

    case 'H':			/* Show new symbol after hash truncation.  */
      alpha_flag_show_after_trunc = 1;
      break;

    case 'h':			/* For gnu-c/vax compatibility.  */
      break;
#endif

    case OPTION_RELAX:
      alpha_flag_relax = 1;
      break;

#ifdef OBJ_ELF
    case OPTION_MDEBUG:
      alpha_flag_mdebug = 1;
      break;
    case OPTION_NO_MDEBUG:
      alpha_flag_mdebug = 0;
      break;
#endif

    default:
      return 0;
    }

  return 1;
}