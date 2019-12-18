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
struct gdbarch {int deprecated_sizeof_call_dummy_words; } ;

/* Variables and functions */

void
set_gdbarch_deprecated_sizeof_call_dummy_words (struct gdbarch *gdbarch,
                                                int deprecated_sizeof_call_dummy_words)
{
  gdbarch->deprecated_sizeof_call_dummy_words = deprecated_sizeof_call_dummy_words;
}