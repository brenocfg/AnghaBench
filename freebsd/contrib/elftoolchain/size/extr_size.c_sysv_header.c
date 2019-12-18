#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ar_name; } ;
typedef  TYPE_1__ Elf_Arhdr ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  tbl_append () ; 
 int /*<<< orphan*/  tbl_new (int) ; 
 int /*<<< orphan*/  tbl_print (char*,int) ; 
 scalar_t__ text_size_total ; 

__attribute__((used)) static void
sysv_header(const char *name, Elf_Arhdr *arhdr)
{

	text_size_total = 0;
	if (arhdr != NULL)
		(void) printf("%s   (ex %s):\n", arhdr->ar_name, name);
	else
		(void) printf("%s  :\n", name);
	tbl_new(3);
	tbl_append();
	tbl_print("section", 0);
	tbl_print("size", 1);
	tbl_print("addr", 2);
}