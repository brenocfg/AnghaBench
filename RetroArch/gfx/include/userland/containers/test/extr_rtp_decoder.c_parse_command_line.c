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
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,char*) ; 
 int do_print_usage ; 
 char* packet_save_file ; 
 int packet_save_is_pktfile ; 
 char* read_uri ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int verbosity ; 

__attribute__((used)) static void parse_command_line(int argc, char **argv)
{
   int arg = 1;

   while (arg < argc)
   {
      if (*argv[arg] != '-')  /* End of options, next should be URI */
         break;

      switch (argv[arg][1])
      {
      case 'h':
         do_print_usage = true;
         break;
      case 's':
         arg++;
         if (arg >= argc)
            break;
         packet_save_file = argv[arg];
         packet_save_is_pktfile = (strncmp(packet_save_file, "pktfile:", 8) == 0);
         break;
      case 'v':
         {
            const char *ptr = &argv[arg][2];

            verbosity = 1;
            while (*ptr++ == 'v')
               verbosity++;
         }
         break;
      default: LOG_ERROR(NULL, "Unrecognised option: %s", argv[arg]); return;
      }

      arg++;
   }

   if (arg < argc)
      read_uri = argv[arg];
}