#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ddg_scc_ptr ;
struct TYPE_4__ {scalar_t__ num_backarcs; struct TYPE_4__* backarcs; int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_scc (ddg_scc_ptr scc)
{
  if (!scc)
    return;

  sbitmap_free (scc->nodes);
  if (scc->num_backarcs > 0)
    free (scc->backarcs);
  free (scc);
}