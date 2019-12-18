#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  segT ;
typedef  char* offsetT ;
struct TYPE_5__ {int /*<<< orphan*/  frch_obstack; TYPE_2__* frch_last; struct TYPE_5__* frch_next; } ;
typedef  TYPE_1__ frchainS ;
struct TYPE_6__ {char* fr_fix; int fr_literal; scalar_t__ fr_next; } ;
typedef  TYPE_2__ fragS ;
struct TYPE_7__ {TYPE_1__* frchainP; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ obstack_next_free (int /*<<< orphan*/ *) ; 
 TYPE_3__* seg_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static offsetT
get_frag_fix (fragS *frag, segT seg)
{
  frchainS *fr;

  if (frag->fr_next)
    return frag->fr_fix;

  /* If a fragment is the last in the chain, special measures must be
     taken to find its size before relaxation, since it may be pending
     on some subsegment chain.  */
  for (fr = seg_info (seg)->frchainP; fr; fr = fr->frch_next)
    if (fr->frch_last == frag)
      return (char *) obstack_next_free (&fr->frch_obstack) - frag->fr_literal;

  abort ();
}