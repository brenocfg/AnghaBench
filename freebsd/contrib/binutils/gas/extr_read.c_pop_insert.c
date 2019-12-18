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
struct TYPE_3__ {scalar_t__ poc_name; } ;
typedef  TYPE_1__ pseudo_typeS ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char* hash_insert (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  po_hash ; 
 int /*<<< orphan*/  pop_override_ok ; 
 int /*<<< orphan*/  pop_table_name ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
pop_insert (const pseudo_typeS *table)
{
  const char *errtxt;
  const pseudo_typeS *pop;
  for (pop = table; pop->poc_name; pop++)
    {
      errtxt = hash_insert (po_hash, pop->poc_name, (char *) pop);
      if (errtxt && (!pop_override_ok || strcmp (errtxt, "exists")))
	as_fatal (_("error constructing %s pseudo-op table: %s"), pop_table_name,
		  errtxt);
    }
}