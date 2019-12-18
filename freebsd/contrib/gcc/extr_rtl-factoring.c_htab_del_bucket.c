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
typedef  TYPE_1__* p_hash_bucket ;
struct TYPE_3__ {scalar_t__ seq_candidates; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  htab_delete (scalar_t__) ; 

__attribute__((used)) static void
htab_del_bucket (void *p)
{
  p_hash_bucket bucket = (p_hash_bucket) p;

  if (bucket->seq_candidates)
    htab_delete (bucket->seq_candidates);

  free (bucket);
}