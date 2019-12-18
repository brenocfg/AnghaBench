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
struct see_mentioned_reg_data {int mentioned; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum extension_type { ____Placeholder_extension_type } extension_type ;

/* Variables and functions */
 int DEF_EXTENSION ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int USE_EXTENSION ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note_uses (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct see_mentioned_reg_data*) ; 
 scalar_t__ reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  see_get_extension_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  see_mentioned_reg ; 

__attribute__((used)) static bool
see_want_to_be_merged_with_extension (rtx ref, rtx extension,
   				      enum extension_type type)
{
  rtx pat;
  rtx dest_extension_reg = see_get_extension_reg (extension, 1);
  rtx source_extension_reg = see_get_extension_reg (extension, 0);
  enum rtx_code code;
  struct see_mentioned_reg_data d;
  int i;

  pat = PATTERN (ref);
  code = GET_CODE (pat);

  if (code == PARALLEL)
    {
      for (i = 0; i < XVECLEN (pat, 0); i++)
	{
	  rtx sub = XVECEXP (pat, 0, i);

	  if (GET_CODE (sub) == SET
	      && (REG_P (SET_DEST (sub))
		  || (GET_CODE (SET_DEST (sub)) == SUBREG
		      && REG_P (SUBREG_REG (SET_DEST (sub)))))
	      && (REG_P (SET_SRC (sub))
		  || (GET_CODE (SET_SRC (sub)) == SUBREG
		      && REG_P (SUBREG_REG (SET_SRC (sub))))))
	    {
	      /* This is a simple move SET.  */
	      if (type == DEF_EXTENSION
		  && reg_mentioned_p (source_extension_reg, SET_DEST (sub)))
		return false;
	    }
	  else
	    {
	      /* This is not a simple move SET.
		 Check if it uses the source of the extension.  */
	      if (type == USE_EXTENSION)
		{
  		  d.reg = dest_extension_reg;
		  d.mentioned = false;
		  note_uses (&sub, see_mentioned_reg, &d);
		  if (d.mentioned)
		    return true;
		}
	    }
	}
      if (type == USE_EXTENSION)
	return false;
    }
  else
    {
      if (code == SET
	  && (REG_P (SET_DEST (pat))
	      || (GET_CODE (SET_DEST (pat)) == SUBREG
		  && REG_P (SUBREG_REG (SET_DEST (pat)))))
	  && (REG_P (SET_SRC (pat))
	      || (GET_CODE (SET_SRC (pat)) == SUBREG
		  && REG_P (SUBREG_REG (SET_SRC (pat))))))
	/* This is a simple move SET.  */
	return false;
     }

  return true;
}