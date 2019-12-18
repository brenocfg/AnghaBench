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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  _dump_field (char*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,int,unsigned int) ; 

__attribute__((used)) static void _dump_node_name(unsigned int lpar_id, u64 n1, u64 n2, u64 n3,
	u64 n4, const char *func, int line)
{
	pr_debug("%s:%d: lpar: %u\n", func, line, lpar_id);
	_dump_field("n1: ", n1, func, line);
	_dump_field("n2: ", n2, func, line);
	_dump_field("n3: ", n3, func, line);
	_dump_field("n4: ", n4, func, line);
}