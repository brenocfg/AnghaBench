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
struct TYPE_2__ {void* error; } ;

/* Variables and functions */
 int FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 void* _ (char*) ; 
 TYPE_1__ inst ; 
 int parse_immediate (char**,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int
parse_ror (char **str)
{
  int rot;
  char *s = *str;

  if (strncasecmp (s, "ROR", 3) == 0)
    s += 3;
  else
    {
      inst.error = _("missing rotation field after comma");
      return FAIL;
    }

  if (parse_immediate (&s, &rot, 0, 24, FALSE) == FAIL)
    return FAIL;

  switch (rot)
    {
    case  0: *str = s; return 0x0;
    case  8: *str = s; return 0x1;
    case 16: *str = s; return 0x2;
    case 24: *str = s; return 0x3;

    default:
      inst.error = _("rotation can only be 0, 8, 16, or 24");
      return FAIL;
    }
}