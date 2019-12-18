#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* help; char* option; } ;

/* Variables and functions */
 size_t LAST_PARAM ; 
 char* _ (char const*) ; 
 TYPE_1__* compiler_params ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* undocumented_msg ; 
 int /*<<< orphan*/  wrap_help (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_param_help (void)
{
  size_t i;

  puts (_("The --param option recognizes the following as parameters:\n"));

  for (i = 0; i < LAST_PARAM; i++)
    {
      const char *help = compiler_params[i].help;
      const char *param = compiler_params[i].option;

      if (help == NULL || *help == '\0')
	help = undocumented_msg;

      /* Get the translation.  */
      help = _(help);

      wrap_help (help, param, strlen (param));
    }

  putchar ('\n');
}