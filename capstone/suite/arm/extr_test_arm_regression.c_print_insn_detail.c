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
typedef  int /*<<< orphan*/  cs_insn ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprint_insn_detail (char*,size_t*,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_insn_detail(cs_insn *ins)
{
	char a_buf[2048];
	size_t cur=0, left=2048;
	snprint_insn_detail(a_buf, &cur, &left, ins);
	printf("%s\n", a_buf);
}