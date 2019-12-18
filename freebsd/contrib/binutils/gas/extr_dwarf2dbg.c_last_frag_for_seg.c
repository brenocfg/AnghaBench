#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct frag {int dummy; } ;
typedef  int /*<<< orphan*/  segT ;
struct TYPE_3__ {struct frag* frch_last; struct TYPE_3__* frch_next; } ;
typedef  TYPE_1__ frchainS ;
struct TYPE_4__ {TYPE_1__* frchainP; } ;

/* Variables and functions */
 TYPE_2__* seg_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct frag *
last_frag_for_seg (segT seg)
{
  frchainS *f = seg_info (seg)->frchainP;

  while (f->frch_next != NULL)
    f = f->frch_next;

  return f->frch_last;
}