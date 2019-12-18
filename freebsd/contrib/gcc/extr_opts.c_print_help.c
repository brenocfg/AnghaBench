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

/* Variables and functions */
 unsigned int CL_COMMON ; 
 int /*<<< orphan*/  GET_ENVIRONMENT (char const*,char*) ; 
 char* _ (char*) ; 
 int atoi (char const*) ; 
 int columns ; 
 char** lang_names ; 
 int /*<<< orphan*/  print_filtered_help (unsigned int) ; 
 int /*<<< orphan*/  print_param_help () ; 
 int /*<<< orphan*/  print_target_help () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void
print_help (void)
{
  size_t i;
  const char *p;

  GET_ENVIRONMENT (p, "COLUMNS");
  if (p)
    {
      int value = atoi (p);
      if (value > 0)
	columns = value;
    }

  puts (_("The following options are language-independent:\n"));

  print_filtered_help (CL_COMMON);
  print_param_help ();

  for (i = 0; lang_names[i]; i++)
    {
      printf (_("The %s front end recognizes the following options:\n\n"),
	      lang_names[i]);
      print_filtered_help (1U << i);
    }
  print_target_help ();
}