#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ diva_trace_ie_t ;
struct TYPE_6__ {scalar_t__ path_length; } ;
typedef  TYPE_2__ diva_man_var_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,char) ; 

__attribute__((used)) static int  diva_strace_read_ie  (diva_man_var_header_t* pVar,
																	diva_trace_ie_t* var) {
	char* ptr = (char*)&pVar->path_length;

	ptr += (pVar->path_length + 1);

	var->length = *ptr;
	memcpy (&var->data[0], ptr+1, *ptr);

	return (0);
}