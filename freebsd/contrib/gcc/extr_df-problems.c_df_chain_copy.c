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
struct df_ref {int dummy; } ;
struct df_link {struct df_link* next; int /*<<< orphan*/  ref; } ;
struct dataflow {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  df_chain_create (struct dataflow*,struct df_ref*,int /*<<< orphan*/ ) ; 

void 
df_chain_copy (struct dataflow *dflow, 
	       struct df_ref *to_ref, 
	       struct df_link *from_ref)
{
  while (from_ref)
    {
      df_chain_create (dflow, to_ref, from_ref->ref);
      from_ref = from_ref->next;
    }
}