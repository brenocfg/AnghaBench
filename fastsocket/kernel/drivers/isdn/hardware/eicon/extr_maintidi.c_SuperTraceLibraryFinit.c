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
struct TYPE_2__ {scalar_t__ hAdapter; } ;
typedef  TYPE_1__ diva_strace_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  SuperTraceCloseAdapter (scalar_t__) ; 

__attribute__((used)) static int SuperTraceLibraryFinit (void* hLib) {
	diva_strace_context_t* pLib = (diva_strace_context_t*)hLib;
	if (pLib) {
		if (pLib->hAdapter) {
			SuperTraceCloseAdapter  (pLib->hAdapter);
		}
		return (0);
	}
	return (-1);
}