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
typedef  int /*<<< orphan*/  symbolS ;

/* Variables and functions */
 int /*<<< orphan*/  S_SET_EXTERNAL (int /*<<< orphan*/ *) ; 
 char* input_line_pointer ; 

void
ia64_check_label (symbolS *label)
{
  if (*input_line_pointer == ':')
    {
      S_SET_EXTERNAL (label);
      input_line_pointer++;
    }
}