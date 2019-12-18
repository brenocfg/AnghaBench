#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__** redirection; } ;
struct TYPE_3__ {int inf_handle; scalar_t__ file_name; } ;

/* Variables and functions */
 int DBG_HANDLES ; 
 int _get_dev_info (int) ; 
 TYPE_2__ child_cmd ; 
 int /*<<< orphan*/  inf_mode_valid ; 
 scalar_t__ inf_terminal_mode ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 

__attribute__((used)) static void
go32_terminal_info (char *args, int from_tty)
{
  printf_unfiltered ("Inferior's terminal is in %s mode.\n",
		     !inf_mode_valid
		     ? "default" : inf_terminal_mode ? "raw" : "cooked");

#if __DJGPP_MINOR__ > 2
  if (child_cmd.redirection)
  {
    int i;

    for (i = 0; i < DBG_HANDLES; i++)
    {
      if (child_cmd.redirection[i]->file_name)
	printf_unfiltered ("\tFile handle %d is redirected to `%s'.\n",
			   i, child_cmd.redirection[i]->file_name);
      else if (_get_dev_info (child_cmd.redirection[i]->inf_handle) == -1)
	printf_unfiltered
	  ("\tFile handle %d appears to be closed by inferior.\n", i);
      /* Mask off the raw/cooked bit when comparing device info words.  */
      else if ((_get_dev_info (child_cmd.redirection[i]->inf_handle) & 0xdf)
	       != (_get_dev_info (i) & 0xdf))
	printf_unfiltered
	  ("\tFile handle %d appears to be redirected by inferior.\n", i);
    }
  }
#endif
}