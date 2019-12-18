#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* abbrev; char* command; char* help; } ;
typedef  TYPE_1__ COMMAND_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vcos_assert (TYPE_1__ const*) ; 

void raspicli_display_help(const COMMAND_LIST *commands, const int num_commands)
{
   int i;

   vcos_assert(commands);

   if (!commands)
      return;

   for (i = 0; i < num_commands; i++)
   {
      fprintf(stdout, "-%s, -%s\t: %s\n", commands[i].abbrev,
              commands[i].command, commands[i].help);
   }
}