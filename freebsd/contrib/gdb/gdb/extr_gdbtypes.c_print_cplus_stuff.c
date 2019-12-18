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

/* Variables and functions */
 int /*<<< orphan*/ * TYPE_FIELD_PRIVATE_BITS (struct type*) ; 
 int /*<<< orphan*/ * TYPE_FIELD_PROTECTED_BITS (struct type*) ; 
 int /*<<< orphan*/ * TYPE_FIELD_VIRTUAL_BITS (struct type*) ; 
 scalar_t__ TYPE_NFIELDS (struct type*) ; 
 scalar_t__ TYPE_NFN_FIELDS (struct type*) ; 
 scalar_t__ TYPE_NFN_FIELDS_TOTAL (struct type*) ; 
 scalar_t__ TYPE_N_BASECLASSES (struct type*) ; 
 int /*<<< orphan*/  dump_fn_fieldlists (struct type*,int) ; 
 int /*<<< orphan*/  gdb_print_host_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  print_bit_vector (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  printfi_filtered (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 

__attribute__((used)) static void
print_cplus_stuff (struct type *type, int spaces)
{
  printfi_filtered (spaces, "n_baseclasses %d\n",
		    TYPE_N_BASECLASSES (type));
  printfi_filtered (spaces, "nfn_fields %d\n",
		    TYPE_NFN_FIELDS (type));
  printfi_filtered (spaces, "nfn_fields_total %d\n",
		    TYPE_NFN_FIELDS_TOTAL (type));
  if (TYPE_N_BASECLASSES (type) > 0)
    {
      printfi_filtered (spaces, "virtual_field_bits (%d bits at *",
			TYPE_N_BASECLASSES (type));
      gdb_print_host_address (TYPE_FIELD_VIRTUAL_BITS (type), gdb_stdout);
      printf_filtered (")");

      print_bit_vector (TYPE_FIELD_VIRTUAL_BITS (type),
			TYPE_N_BASECLASSES (type));
      puts_filtered ("\n");
    }
  if (TYPE_NFIELDS (type) > 0)
    {
      if (TYPE_FIELD_PRIVATE_BITS (type) != NULL)
	{
	  printfi_filtered (spaces, "private_field_bits (%d bits at *",
			    TYPE_NFIELDS (type));
	  gdb_print_host_address (TYPE_FIELD_PRIVATE_BITS (type), gdb_stdout);
	  printf_filtered (")");
	  print_bit_vector (TYPE_FIELD_PRIVATE_BITS (type),
			    TYPE_NFIELDS (type));
	  puts_filtered ("\n");
	}
      if (TYPE_FIELD_PROTECTED_BITS (type) != NULL)
	{
	  printfi_filtered (spaces, "protected_field_bits (%d bits at *",
			    TYPE_NFIELDS (type));
	  gdb_print_host_address (TYPE_FIELD_PROTECTED_BITS (type), gdb_stdout);
	  printf_filtered (")");
	  print_bit_vector (TYPE_FIELD_PROTECTED_BITS (type),
			    TYPE_NFIELDS (type));
	  puts_filtered ("\n");
	}
    }
  if (TYPE_NFN_FIELDS (type) > 0)
    {
      dump_fn_fieldlists (type, spaces);
    }
}