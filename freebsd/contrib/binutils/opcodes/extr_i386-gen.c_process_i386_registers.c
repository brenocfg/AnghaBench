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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* next_field (char*,char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* remove_leading_whitespaces (char*) ; 
 int /*<<< orphan*/  remove_trailing_whitespaces (char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void
process_i386_registers (void)
{
  FILE *fp = fopen ("i386-reg.tbl", "r");
  char buf[2048];
  char *str, *p, *last;
  char *reg_name, *reg_type, *reg_flags, *reg_num;

  if (fp == NULL)
    fail (_("can't find i386-reg.tbl for reading\n"));

  printf ("\n/* i386 register table.  */\n\n");
  printf ("const reg_entry i386_regtab[] =\n{\n");

  while (!feof (fp))
    {
      if (fgets (buf, sizeof (buf), fp) == NULL)
	break;

      p = remove_leading_whitespaces (buf);

      /* Skip comments.  */
      str = strstr (p, "//");
      if (str != NULL)
	str[0] = '\0';

      /* Remove trailing white spaces.  */
      remove_trailing_whitespaces (p);

      switch (p[0])
	{
	case '#':
	  printf ("%s\n", p);
	case '\0':
	  continue;
	  break;
	default:
	  break;
	}

      last = p + strlen (p);

      /* Find reg_name.  */
      reg_name = next_field (p, &str);

      if (str >= last)
	abort ();

      /* Find reg_type.  */
      reg_type = next_field (str, &str);

      if (str >= last)
	abort ();

      /* Find reg_flags.  */
      reg_flags = next_field (str, &str);

      if (str >= last)
	abort ();

      /* Find reg_num.  */
      reg_num = next_field (str, &str);

      printf ("  { \"%s\", %s, %s, %s },\n",
	      reg_name, reg_type, reg_flags, reg_num);
    }

  printf ("};\n");

  printf ("\nconst unsigned int i386_regtab_size = ARRAY_SIZE (i386_regtab);\n");
}