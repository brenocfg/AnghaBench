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
struct TYPE_2__ {scalar_t__ error; } ;

/* Variables and functions */
 scalar_t__ BAD_GARBAGE ; 
 scalar_t__ FAIL ; 
 int SUCCESS ; 
 TYPE_1__ inst ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 

__attribute__((used)) static int
end_of_line (char *str)
{
  int retval = SUCCESS;

  skip_whitespace (str);
  if (*str != '\0')
    {
      retval = (int) FAIL;

      if (!inst.error)
        inst.error = BAD_GARBAGE;
    }

  return retval;
}