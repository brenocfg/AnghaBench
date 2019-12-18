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
typedef  int uint ;

/* Variables and functions */
 char* make_signed_hex_str_16 (int /*<<< orphan*/ ) ; 
 char* make_signed_hex_str_32 (int /*<<< orphan*/ ) ; 
 char* make_signed_hex_str_8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_imm_16 () ; 
 int /*<<< orphan*/  read_imm_32 () ; 
 int /*<<< orphan*/  read_imm_8 () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static char* get_imm_str_s(uint size)
{
	static char str[15];
	if(size == 0)
		sprintf(str, "#%s", make_signed_hex_str_8(read_imm_8()));
	else if(size == 1)
		sprintf(str, "#%s", make_signed_hex_str_16(read_imm_16()));
	else
		sprintf(str, "#%s", make_signed_hex_str_32(read_imm_32()));
	return str;
}