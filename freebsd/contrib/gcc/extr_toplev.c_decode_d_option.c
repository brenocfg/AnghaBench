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
 int /*<<< orphan*/  enable_rtl_dump_file (int) ; 
 int flag_debug_asm ; 
 int flag_dump_rtl_in_asm ; 
 int flag_print_asm_name ; 
 int /*<<< orphan*/  graph_dump_format ; 
 int rtl_dump_and_exit ; 
 int set_yydebug ; 
 int /*<<< orphan*/  setup_core_dumping () ; 
 int /*<<< orphan*/  vcg ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int) ; 

void
decode_d_option (const char *arg)
{
  int c;

  while (*arg)
    switch (c = *arg++)
      {
      case 'A':
	flag_debug_asm = 1;
	break;
      case 'p':
	flag_print_asm_name = 1;
	break;
      case 'P':
	flag_dump_rtl_in_asm = 1;
	flag_print_asm_name = 1;
	break;
      case 'v':
	graph_dump_format = vcg;
	break;
      case 'x':
	rtl_dump_and_exit = 1;
	break;
      case 'y':
	set_yydebug = 1;
	break;
      case 'D':	/* These are handled by the preprocessor.  */
      case 'I':
	break;
      case 'H':
	setup_core_dumping();
	break;

      case 'a':
      default:
	if (!enable_rtl_dump_file (c))
	  warning (0, "unrecognized gcc debugging option: %c", c);
	break;
      }
}