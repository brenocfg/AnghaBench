#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int offsetT ;
struct TYPE_3__ {int fr_subtype; int /*<<< orphan*/  fr_symbol; } ;
typedef  TYPE_1__ fragS ;

/* Variables and functions */
 int resolve_symbol_value (int /*<<< orphan*/ ) ; 

int
eh_frame_estimate_size_before_relax (fragS *frag)
{
  offsetT diff;
  int ca = frag->fr_subtype >> 3;
  int ret;

  diff = resolve_symbol_value (frag->fr_symbol);

  if (ca > 0 && diff % ca == 0 && diff / ca < 0x40)
    ret = 0;
  else if (diff < 0x100)
    ret = 1;
  else if (diff < 0x10000)
    ret = 2;
  else
    ret = 4;

  frag->fr_subtype = (frag->fr_subtype & ~7) | ret;

  return ret;
}