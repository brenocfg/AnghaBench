#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fr_type; int fr_address; int fr_fix; char* fr_literal; int fr_var; TYPE_1__* fr_next; } ;
typedef  TYPE_2__ fragS ;
struct TYPE_4__ {int fr_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rs_align_code ; 

void
spu_handle_align (fragS *fragp)
{
  static const unsigned char nop_pattern[8] = {
    0x40, 0x20, 0x00, 0x00, /* even nop */
    0x00, 0x20, 0x00, 0x00, /* odd  nop */
  };

  int bytes;
  char *p;

  if (fragp->fr_type != rs_align_code)
    return;

  bytes = fragp->fr_next->fr_address - fragp->fr_address - fragp->fr_fix;
  p = fragp->fr_literal + fragp->fr_fix;

  if (bytes & 3)
    {
      int fix = bytes & 3;
      memset (p, 0, fix);
      p += fix;
      bytes -= fix;
      fragp->fr_fix += fix;
    }
  if (bytes & 4)
    {
      memcpy (p, &nop_pattern[4], 4);
      p += 4;
      bytes -= 4;
      fragp->fr_fix += 4;
    }

  memcpy (p, nop_pattern, 8);
  fragp->fr_var = 8;
}