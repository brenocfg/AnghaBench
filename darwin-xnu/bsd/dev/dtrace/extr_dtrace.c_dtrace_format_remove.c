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
typedef  int uint16_t ;
struct TYPE_3__ {char** dts_formats; int dts_nformats; } ;
typedef  TYPE_1__ dtrace_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  kmem_free (char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
dtrace_format_remove(dtrace_state_t *state, uint16_t format)
{
	char *fmt;

	ASSERT(state->dts_formats != NULL);
	ASSERT(format <= state->dts_nformats);
	ASSERT(state->dts_formats[format - 1] != NULL);

	fmt = state->dts_formats[format - 1];
	kmem_free(fmt, strlen(fmt) + 1);
	state->dts_formats[format - 1] = NULL;
}