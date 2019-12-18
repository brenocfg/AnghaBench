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
typedef  int /*<<< orphan*/  unichar ;

/* Variables and functions */
 int /*<<< orphan*/  input_stream ; 
 int /*<<< orphan*/  input_stream_pos ; 
 int /*<<< orphan*/  unichar_dup (int /*<<< orphan*/  const*) ; 

void
mc_set_content (const unichar *src)
{
  if (!src)
    return;
  input_stream = input_stream_pos = unichar_dup (src);
}