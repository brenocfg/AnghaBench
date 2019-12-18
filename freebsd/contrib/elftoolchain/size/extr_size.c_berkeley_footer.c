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
 int BUF_SIZE ; 
 scalar_t__ RADIX_DECIMAL ; 
 scalar_t__ RADIX_HEX ; 
 scalar_t__ RADIX_OCTAL ; 
 scalar_t__ bss_size ; 
 int /*<<< orphan*/  bss_size_total ; 
 scalar_t__ data_size ; 
 int /*<<< orphan*/  data_size_total ; 
 scalar_t__ radix ; 
 scalar_t__ show_totals ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  tbl_append () ; 
 int /*<<< orphan*/  tbl_print (char*,int) ; 
 int /*<<< orphan*/  tbl_print_num (scalar_t__,scalar_t__,int) ; 
 scalar_t__ text_size ; 
 int /*<<< orphan*/  text_size_total ; 
 scalar_t__ total_size ; 

__attribute__((used)) static void
berkeley_footer(const char *name, const char *ar_name, const char *msg)
{
	char buf[BUF_SIZE];

	total_size = text_size + data_size + bss_size;
	if (show_totals) {
		text_size_total += text_size;
		bss_size_total += bss_size;
		data_size_total += data_size;
	}

	tbl_append();
	tbl_print_num(text_size, radix, 0);
	tbl_print_num(data_size, radix, 1);
	tbl_print_num(bss_size, radix, 2);
	if (radix == RADIX_OCTAL)
		tbl_print_num(total_size, RADIX_OCTAL, 3);
	else
		tbl_print_num(total_size, RADIX_DECIMAL, 3);
	tbl_print_num(total_size, RADIX_HEX, 4);
	if (ar_name != NULL && name != NULL)
		(void) snprintf(buf, BUF_SIZE, "%s (%s %s)", ar_name, msg,
		    name);
	else if (ar_name != NULL && name == NULL)
		(void) snprintf(buf, BUF_SIZE, "%s (%s)", ar_name, msg);
	else
		(void) snprintf(buf, BUF_SIZE, "%s", name);
	tbl_print(buf, 5);
}