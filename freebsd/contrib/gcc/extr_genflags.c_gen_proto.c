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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 char* XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_macro (char const*,int,int) ; 
 char* max_id_len ; 
 int maybe_eval_c_test (char*) ; 
 int num_operands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void
gen_proto (rtx insn)
{
  int num = num_operands (insn);
  int i;
  const char *name = XSTR (insn, 0);
  int truth = maybe_eval_c_test (XSTR (insn, 2));

  /* Many md files don't refer to the last two operands passed to the
     call patterns.  This means their generator functions will be two
     arguments too short.  Instead of changing every md file to touch
     those operands, we wrap the prototypes in macros that take the
     correct number of arguments.  */
  if (name[0] == 'c' || name[0] == 's')
    {
      if (!strcmp (name, "call")
	  || !strcmp (name, "call_pop")
	  || !strcmp (name, "sibcall")
	  || !strcmp (name, "sibcall_pop"))
	gen_macro (name, num, 4);
      else if (!strcmp (name, "call_value")
	       || !strcmp (name, "call_value_pop")
	       || !strcmp (name, "sibcall_value")
	       || !strcmp (name, "sibcall_value_pop"))
	gen_macro (name, num, 5);
    }

  if (truth != 0)
    printf ("extern rtx        gen_%-*s (", max_id_len, name);
  else
    printf ("static inline rtx gen_%-*s (", max_id_len, name);

  if (num == 0)
    fputs ("void", stdout);
  else
    {
      for (i = 1; i < num; i++)
	fputs ("rtx, ", stdout);

      fputs ("rtx", stdout);
    }

  puts (");");

  /* Some back ends want to take the address of generator functions,
     so we cannot simply use #define for these dummy definitions.  */
  if (truth == 0)
    {
      printf ("static inline rtx\ngen_%s", name);
      if (num > 0)
	{
	  putchar ('(');
	  for (i = 0; i < num-1; i++)
	    printf ("rtx ARG_UNUSED (%c), ", 'a' + i);
	  printf ("rtx ARG_UNUSED (%c))\n", 'a' + i);
	}
      else
	puts ("(void)");
      puts ("{\n  return 0;\n}");
    }

}