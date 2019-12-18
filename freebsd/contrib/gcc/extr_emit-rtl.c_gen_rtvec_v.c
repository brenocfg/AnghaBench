#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  TYPE_1__* rtvec ;
struct TYPE_5__ {int /*<<< orphan*/ * elem; } ;

/* Variables and functions */
 TYPE_1__* NULL_RTVEC ; 
 TYPE_1__* rtvec_alloc (int) ; 

rtvec
gen_rtvec_v (int n, rtx *argp)
{
  int i;
  rtvec rt_val;

  if (n == 0)
    return NULL_RTVEC;		/* Don't allocate an empty rtvec...	*/

  rt_val = rtvec_alloc (n);	/* Allocate an rtvec...			*/

  for (i = 0; i < n; i++)
    rt_val->elem[i] = *argp++;

  return rt_val;
}