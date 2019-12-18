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
 int /*<<< orphan*/  PUT_NUM_ELEM (TYPE_1__*,int) ; 
 TYPE_1__* ggc_alloc_rtvec (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtvec_alloc_counts ; 
 int rtvec_alloc_sizes ; 

rtvec
rtvec_alloc (int n)
{
  rtvec rt;

  rt = ggc_alloc_rtvec (n);
  /* Clear out the vector.  */
  memset (&rt->elem[0], 0, n * sizeof (rtx));

  PUT_NUM_ELEM (rt, n);

#ifdef GATHER_STATISTICS
  rtvec_alloc_counts++;
  rtvec_alloc_sizes += n * sizeof (rtx);
#endif

  return rt;
}