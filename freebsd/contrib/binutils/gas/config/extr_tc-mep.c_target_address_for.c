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
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_3__ {int fr_offset; int /*<<< orphan*/ * fr_symbol; } ;
typedef  TYPE_1__ fragS ;

/* Variables and functions */
 scalar_t__ S_GET_VALUE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
target_address_for (fragS *frag)
{
  int rv = frag->fr_offset;
  symbolS *sym = frag->fr_symbol;

  if (sym)
    rv += S_GET_VALUE (sym);

  return rv;
}