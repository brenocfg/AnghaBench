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
struct TYPE_3__ {scalar_t__ path_length; } ;
typedef  TYPE_1__ diva_man_var_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,char) ; 

__attribute__((used)) static int diva_strace_read_asc  (diva_man_var_header_t* pVar, char* var) {
	char* ptr = (char*)&pVar->path_length;

	ptr += (pVar->path_length + 1);
	memcpy (var, ptr+1, *ptr);
	var[(int)*ptr] = 0;

	return (0);
}