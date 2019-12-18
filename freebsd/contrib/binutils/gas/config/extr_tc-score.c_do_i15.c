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
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  _IMM15 ; 
 int data_op2 (char**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_of_line (char*) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 

__attribute__((used)) static void
do_i15 (char *str)
{
  skip_whitespace (str);

  if (data_op2 (&str, 10, _IMM15) != (int) FAIL)
    end_of_line (str);
}