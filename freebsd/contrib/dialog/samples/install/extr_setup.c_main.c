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
 int /*<<< orphan*/  dialog_clear () ; 
 int dialog_menu (char*,char*,int,int,int,int,char**) ; 
 int dialog_textbox (char*,char*,int,int) ; 
 int /*<<< orphan*/  end_dialog () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  init_dialog () ; 
 int /*<<< orphan*/  main_install () ; 
 scalar_t__ num_linux ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* progname ; 
 int /*<<< orphan*/  read_partitions () ; 

int
main(int argc, char **argv)
{
    int stop = 0;
    int ret;
    char *items1[] =
    {
	"1", "Display a help text",
	"2", "Start an installation",
	"3", "Exit to the shell"
    };

    progname = argv[0];

    read_partitions();
    if (num_linux == 0) {
	printf("\n\nPlease start \"fdisk\" or \"cfdisk\" and create a"
	       "\nnative Linux-partition to install Linux on.\n\n");
	exit(1);
    }

    init_dialog();

    while (!stop) {
	ret = dialog_menu("Linux Install Utility",
			  "\\nCopyright (C) 1995 Florian La Roche\\n"
			  "\\nPre-Alpha version, be careful, read the doc!!!"
			  "\\nemail: florian@jurix.jura.uni-sb.de, "
			  "flla@stud.uni-sb.de\\n",
			  15, 64, 3, 3, items1);
	dialog_clear();
	switch (ret) {
	case 0:
	    ret = dialog_textbox("Help Text",
				 "setup.help", 20, 70);
	    dialog_clear();
	    break;
	case 1:
	    main_install();
	    break;
	case 2:
	    stop = 1;
	    break;
	case -2:		/* cancel */
	case -1:
	    stop = 1;		/* esc */
	}
    }
    end_dialog();
    printf("\nExecute \"reboot\" to restart your computer...\n");

    exit(0);
}