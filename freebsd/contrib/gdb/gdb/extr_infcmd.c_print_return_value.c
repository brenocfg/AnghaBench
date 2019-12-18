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
struct value {int dummy; } ;
struct ui_stream {int /*<<< orphan*/  stream; } ;
struct type {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int /*<<< orphan*/  DEPRECATED_EXTRACT_STRUCT_VALUE_ADDRESS (int /*<<< orphan*/ ) ; 
 scalar_t__ DEPRECATED_EXTRACT_STRUCT_VALUE_ADDRESS_P () ; 
 int /*<<< orphan*/  EXTRACT_RETURN_VALUE (struct type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RETURN_VALUE_STRUCT_CONVENTION ; 
 int /*<<< orphan*/  TYPE_NAME (struct type*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS_RAW (struct value*) ; 
 int /*<<< orphan*/  Val_no_prettyprint ; 
 struct value* allocate_value (struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 scalar_t__ gdbarch_return_value (int /*<<< orphan*/ ,struct type*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gdbarch_return_value_p (int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup_ui_out_stream_delete (struct ui_stream*) ; 
 int /*<<< orphan*/  record_latest_value (struct value*) ; 
 struct value* register_value_being_returned (struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_registers ; 
 int /*<<< orphan*/  ui_out_field_fmt (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_stream (int /*<<< orphan*/ ,char*,struct ui_stream*) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct ui_stream* ui_out_stream_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 
 struct value* value_at (struct type*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  value_print (struct value*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_return_value (int struct_return, struct type *value_type)
{
  struct cleanup *old_chain;
  struct ui_stream *stb;
  struct value *value;

  if (!struct_return)
    {
      /* The return value can be found in the inferior's registers.  */
      value = register_value_being_returned (value_type, stop_registers);
    }
  /* FIXME: cagney/2004-01-17: When both return_value and
     extract_returned_value_address are available, should use that to
     find the address of and then extract the returned value.  */
  /* FIXME: 2003-09-27: When returning from a nested inferior function
     call, it's possible (with no help from the architecture vector)
     to locate and return/print a "struct return" value.  This is just
     a more complicated case of what is already being done in in the
     inferior function call code.  In fact, when inferior function
     calls are made async, this will likely be made the norm.  */
  else if (gdbarch_return_value_p (current_gdbarch))
    /* We cannot determine the contents of the structure because it is
       on the stack, and we don't know where, since we did not
       initiate the call, as opposed to the call_function_by_hand
       case.  */
    {
      gdb_assert (gdbarch_return_value (current_gdbarch, value_type,
					NULL, NULL, NULL)
		  == RETURN_VALUE_STRUCT_CONVENTION);
      ui_out_text (uiout, "Value returned has type: ");
      ui_out_field_string (uiout, "return-type", TYPE_NAME (value_type));
      ui_out_text (uiout, ".");
      ui_out_text (uiout, " Cannot determine contents\n");
      return;
    }
  else
    {
      if (DEPRECATED_EXTRACT_STRUCT_VALUE_ADDRESS_P ())
	{
	  CORE_ADDR addr = DEPRECATED_EXTRACT_STRUCT_VALUE_ADDRESS (stop_registers);
	  if (!addr)
	    error ("Function return value unknown.");
	  value = value_at (value_type, addr, NULL);
	}
      else
	{
	  /* It is "struct return" yet the value is being extracted,
             presumably from registers, using EXTRACT_RETURN_VALUE.
             This doesn't make sense.  Unfortunately, the legacy
             interfaces allowed this behavior.  Sigh!  */
	  value = allocate_value (value_type);
	  CHECK_TYPEDEF (value_type);
	  /* If the function returns void, don't bother fetching the
	     return value.  */
	  EXTRACT_RETURN_VALUE (value_type, stop_registers,
				VALUE_CONTENTS_RAW (value));
	}
    }

  /* Print it.  */
  stb = ui_out_stream_new (uiout);
  old_chain = make_cleanup_ui_out_stream_delete (stb);
  ui_out_text (uiout, "Value returned is ");
  ui_out_field_fmt (uiout, "gdb-result-var", "$%d",
		    record_latest_value (value));
  ui_out_text (uiout, " = ");
  value_print (value, stb->stream, 0, Val_no_prettyprint);
  ui_out_field_stream (uiout, "return-value", stb);
  ui_out_text (uiout, "\n");
  do_cleanups (old_chain);
}