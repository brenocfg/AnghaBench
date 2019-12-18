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
typedef  int /*<<< orphan*/  symbolS ;

/* Variables and functions */
 int AXP_REG_AT ; 
 size_t AXP_REG_FP ; 
 size_t AXP_REG_SP ; 
 int /*<<< orphan*/  ISDIGIT (char) ; 
 int /*<<< orphan*/  _ (char*) ; 
 size_t alpha_gp_register ; 
 int /*<<< orphan*/  alpha_noat_on ; 
 int /*<<< orphan*/ ** alpha_register_table ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 

symbolS *
md_undefined_symbol (char *name)
{
  if (*name == '$')
    {
      int is_float = 0, num;

      switch (*++name)
	{
	case 'f':
	  if (name[1] == 'p' && name[2] == '\0')
	    return alpha_register_table[AXP_REG_FP];
	  is_float = 32;
	  /* Fall through.  */

	case 'r':
	  if (!ISDIGIT (*++name))
	    break;
	  /* Fall through.  */

	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	  if (name[1] == '\0')
	    num = name[0] - '0';
	  else if (name[0] != '0' && ISDIGIT (name[1]) && name[2] == '\0')
	    {
	      num = (name[0] - '0') * 10 + name[1] - '0';
	      if (num >= 32)
		break;
	    }
	  else
	    break;

	  if (!alpha_noat_on && (num + is_float) == AXP_REG_AT)
	    as_warn (_("Used $at without \".set noat\""));
	  return alpha_register_table[num + is_float];

	case 'a':
	  if (name[1] == 't' && name[2] == '\0')
	    {
	      if (!alpha_noat_on)
		as_warn (_("Used $at without \".set noat\""));
	      return alpha_register_table[AXP_REG_AT];
	    }
	  break;

	case 'g':
	  if (name[1] == 'p' && name[2] == '\0')
	    return alpha_register_table[alpha_gp_register];
	  break;

	case 's':
	  if (name[1] == 'p' && name[2] == '\0')
	    return alpha_register_table[AXP_REG_SP];
	  break;
	}
    }
  return NULL;
}