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
struct macro_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_buffer (struct macro_buffer*) ; 

__attribute__((used)) static void
cleanup_macro_buffer (void *untyped_buf)
{
  free_buffer ((struct macro_buffer *) untyped_buf);
}