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
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dialog_clear () ; 
 int dialog_menu (char*,char*,int,int,int,int,char**) ; 
 int /*<<< orphan*/  install_harddisk () ; 
 int /*<<< orphan*/  install_nfs () ; 
 char const* install_partition ; 
 int /*<<< orphan*/  install_premounted () ; 
 scalar_t__ my_system (char*,char const*,...) ; 
 int /*<<< orphan*/  null ; 
 scalar_t__ num_linux ; 
 TYPE_1__* partitions ; 
 int select_install_partition () ; 

__attribute__((used)) static void
main_install(void)
{
    int part, ret;
    const char *name;
    char *items1[] =
    {
	"1", "Harddisk Install",
	"2", "Network Install(NFS)",
	"3", "Premounted on /source"
    };

    if (num_linux == 0) {
	/* XXX */
	return;
    }
    if ((part = select_install_partition()) <= -1)
	return;
    install_partition = name = partitions[part].name;
    if (my_system("mke2fs %s %s", name, null))
	return;
    if (my_system("mount -t ext2 %s /install %s", name, null))
	return;
    ret = dialog_menu("Choose install medium",
		      "\\nPlease say from where you want to install.\\n",
		      12, 62, 3, 3, items1);
    dialog_clear();
    switch (ret) {
    case 0:
	install_harddisk();
	break;
    case 1:
	install_nfs();
	break;
    case 2:
	install_premounted();
	break;
    case -2:			/* cancel */
    case -1:
	break;			/* esc */
    }
    if (my_system("umount /install %s", null))
	return;
}