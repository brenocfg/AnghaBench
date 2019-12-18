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
 int FORMAT_BSD ; 
 int FORMAT_POSIX ; 
 int FORMAT_SYSV ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * format ; 
 int /*<<< orphan*/ * formats ; 

__attribute__((used)) static void
set_output_format (char *f)
{
  int i;

  switch (*f)
    {
    case 'b':
    case 'B':
      i = FORMAT_BSD;
      break;
    case 'p':
    case 'P':
      i = FORMAT_POSIX;
      break;
    case 's':
    case 'S':
      i = FORMAT_SYSV;
      break;
    default:
      fatal (_("%s: invalid output format"), f);
    }
  format = &formats[i];
}