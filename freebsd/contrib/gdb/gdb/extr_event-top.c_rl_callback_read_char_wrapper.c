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
typedef  int /*<<< orphan*/  gdb_client_data ;

/* Variables and functions */
 int /*<<< orphan*/  after_char_processing_hook () ; 
 int /*<<< orphan*/  rl_callback_read_char () ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void
rl_callback_read_char_wrapper (gdb_client_data client_data)
{
  rl_callback_read_char ();
  if (after_char_processing_hook)
    (*after_char_processing_hook) ();
}