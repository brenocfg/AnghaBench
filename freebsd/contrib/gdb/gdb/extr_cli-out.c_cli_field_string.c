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
struct ui_out {int dummy; } ;
typedef  enum ui_align { ____Placeholder_ui_align } ui_align ;
struct TYPE_3__ {scalar_t__ suppress_output; } ;
typedef  TYPE_1__ cli_out_data ;

/* Variables and functions */
 int /*<<< orphan*/  field_separator () ; 
 int /*<<< orphan*/  out_field_fmt (struct ui_out*,int,char const*,char*,char const*) ; 
 int strlen (char const*) ; 
 int ui_left ; 
 int ui_noalign ; 
 TYPE_1__* ui_out_data (struct ui_out*) ; 
 int /*<<< orphan*/  ui_out_spaces (struct ui_out*,int) ; 
 int ui_right ; 

void
cli_field_string (struct ui_out *uiout,
		  int fldno,
		  int width,
		  enum ui_align align,
		  const char *fldname,
		  const char *string)
{
  int before = 0;
  int after = 0;

  cli_out_data *data = ui_out_data (uiout);
  if (data->suppress_output)
    return;

  if ((align != ui_noalign) && string)
    {
      before = width - strlen (string);
      if (before <= 0)
	before = 0;
      else
	{
	  if (align == ui_right)
	    after = 0;
	  else if (align == ui_left)
	    {
	      after = before;
	      before = 0;
	    }
	  else
	    /* ui_center */
	    {
	      after = before / 2;
	      before -= after;
	    }
	}
    }

  if (before)
    ui_out_spaces (uiout, before);
  if (string)
    out_field_fmt (uiout, fldno, fldname, "%s", string);
  if (after)
    ui_out_spaces (uiout, after);

  if (align != ui_noalign)
    field_separator ();
}