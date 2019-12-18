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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int ledd_status; } ;

/* Variables and functions */
 TYPE_1__* hotk ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static int
proc_read_ledd(char *page, char **start, off_t off, int count, int *eof,
	       void *data)
{
	return sprintf(page, "0x%08x\n", hotk->ledd_status);
}