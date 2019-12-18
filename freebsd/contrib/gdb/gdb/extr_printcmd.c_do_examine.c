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
struct type {int dummy; } ;
struct format_data {char format; char size; int count; } ;
typedef  int /*<<< orphan*/  asection ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  QUIT ; 
 struct type* examine_b_type ; 
 struct type* examine_g_type ; 
 struct type* examine_h_type ; 
 struct type* examine_i_type ; 
 struct type* examine_w_type ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  last_examine_address ; 
 scalar_t__ last_examine_value ; 
 int /*<<< orphan*/  next_address ; 
 int /*<<< orphan*/ * next_section ; 
 int /*<<< orphan*/  print_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_formatted (scalar_t__,char,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  release_value (scalar_t__) ; 
 scalar_t__ value_at_lazy (struct type*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  value_free (scalar_t__) ; 

__attribute__((used)) static void
do_examine (struct format_data fmt, CORE_ADDR addr, asection *sect)
{
  char format = 0;
  char size;
  int count = 1;
  struct type *val_type = NULL;
  int i;
  int maxelts;

  format = fmt.format;
  size = fmt.size;
  count = fmt.count;
  next_address = addr;
  next_section = sect;

  /* String or instruction format implies fetch single bytes
     regardless of the specified size.  */
  if (format == 's' || format == 'i')
    size = 'b';

  if (format == 'i')
    val_type = examine_i_type;
  else if (size == 'b')
    val_type = examine_b_type;
  else if (size == 'h')
    val_type = examine_h_type;
  else if (size == 'w')
    val_type = examine_w_type;
  else if (size == 'g')
    val_type = examine_g_type;

  maxelts = 8;
  if (size == 'w')
    maxelts = 4;
  if (size == 'g')
    maxelts = 2;
  if (format == 's' || format == 'i')
    maxelts = 1;

  /* Print as many objects as specified in COUNT, at most maxelts per line,
     with the address of the next one at the start of each line.  */

  while (count > 0)
    {
      QUIT;
      print_address (next_address, gdb_stdout);
      printf_filtered (":");
      for (i = maxelts;
	   i > 0 && count > 0;
	   i--, count--)
	{
	  printf_filtered ("\t");
	  /* Note that print_formatted sets next_address for the next
	     object.  */
	  last_examine_address = next_address;

	  if (last_examine_value)
	    value_free (last_examine_value);

	  /* The value to be displayed is not fetched greedily.
	     Instead, to avoid the posibility of a fetched value not
	     being used, its retreval is delayed until the print code
	     uses it.  When examining an instruction stream, the
	     disassembler will perform its own memory fetch using just
	     the address stored in LAST_EXAMINE_VALUE.  FIXME: Should
	     the disassembler be modified so that LAST_EXAMINE_VALUE
	     is left with the byte sequence from the last complete
	     instruction fetched from memory? */
	  last_examine_value = value_at_lazy (val_type, next_address, sect);

	  if (last_examine_value)
	    release_value (last_examine_value);

	  print_formatted (last_examine_value, format, size, gdb_stdout);
	}
      printf_filtered ("\n");
      gdb_flush (gdb_stdout);
    }
}