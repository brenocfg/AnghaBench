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

/* Variables and functions */
 int /*<<< orphan*/  cjkcode ; 
 int column ; 
 int /*<<< orphan*/  line ; 
 int uc_width (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_line_column (unsigned int uc, void* data)
{
  if (uc == 0x000A) {
    line++;
    column = 0;
  } else {
    int width = uc_width(uc, cjkcode);
    if (width >= 0)
      column += width;
    else if (uc == 0x0009)
      column += 8 - (column % 8);
  }
}