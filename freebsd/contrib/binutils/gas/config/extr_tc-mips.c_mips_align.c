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
typedef  int /*<<< orphan*/  valueT ;
typedef  int /*<<< orphan*/  symbolS ;

/* Variables and functions */
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  frag_align (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_now ; 
 scalar_t__ frag_now_fix () ; 
 int /*<<< orphan*/  mips_emit_delays () ; 
 scalar_t__ now_seg ; 
 int /*<<< orphan*/  record_alignment (scalar_t__,int) ; 
 int /*<<< orphan*/  symbol_set_frag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_align (int to, int fill, symbolS *label)
{
  mips_emit_delays ();
  frag_align (to, fill, 0);
  record_alignment (now_seg, to);
  if (label != NULL)
    {
      assert (S_GET_SEGMENT (label) == now_seg);
      symbol_set_frag (label, frag_now);
      S_SET_VALUE (label, (valueT) frag_now_fix ());
    }
}