#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct loops {unsigned int num; TYPE_1__** parray; } ;
struct TYPE_2__ {int /*<<< orphan*/  nb_iterations; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  already_instantiated ; 
 struct loops* current_loops ; 
 int /*<<< orphan*/  del_scev_info ; 
 int /*<<< orphan*/  eq_scev_info ; 
 int /*<<< orphan*/  hash_scev_info ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_scalar_evolutions_analyzer () ; 
 int /*<<< orphan*/  scalar_evolution_info ; 

void
scev_initialize (struct loops *loops)
{
  unsigned i;
  current_loops = loops;

  scalar_evolution_info = htab_create (100, hash_scev_info,
				       eq_scev_info, del_scev_info);
  already_instantiated = BITMAP_ALLOC (NULL);
  
  initialize_scalar_evolutions_analyzer ();

  for (i = 1; i < loops->num; i++)
    if (loops->parray[i])
      loops->parray[i]->nb_iterations = NULL_TREE;
}