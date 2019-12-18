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
struct TYPE_3__ {int /*<<< orphan*/ * next; scalar_t__ base; scalar_t__ limit; } ;
typedef  TYPE_1__ tokenrun ;

/* Variables and functions */
 scalar_t__ XNEWVEC (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cpp_token ; 

void
_cpp_init_tokenrun (tokenrun *run, unsigned int count)
{
  run->base = XNEWVEC (cpp_token, count);
  run->limit = run->base + count;
  run->next = NULL;
}