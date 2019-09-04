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
struct san_src_loc {char* filename; int line; int col; } ;

/* Variables and functions */
 int line_acquired ; 
 size_t snprintf (char*,size_t,char*,char*,int,int) ; 

__attribute__((used)) static size_t
format_loc(struct san_src_loc *loc, char *dst, size_t sz)
{
	return snprintf(dst, sz, "  loc: %s:%d:%d\n",
			loc->filename,
			loc->line & ~line_acquired,
			loc->col
		);
}