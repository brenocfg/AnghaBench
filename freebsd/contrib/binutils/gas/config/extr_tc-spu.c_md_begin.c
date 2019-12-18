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
struct TYPE_2__ {int /*<<< orphan*/  mnemonic; } ;
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char* hash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_new () ; 
 int /*<<< orphan*/  op_hash ; 
 int spu_num_opcodes ; 
 TYPE_1__* spu_opcodes ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
md_begin (void)
{
  const char *retval = NULL;
  int i;

  /* initialize hash table */

  op_hash = hash_new ();

  /* loop until you see the end of the list */

  for (i = 0; i < spu_num_opcodes; i++)
    {
      /* hash each mnemonic and record its position */

      retval = hash_insert (op_hash, spu_opcodes[i].mnemonic, (PTR)&spu_opcodes[i]);

      if (retval != NULL && strcmp (retval, "exists") != 0)
	as_fatal (_("Can't hash instruction '%s':%s"),
		  spu_opcodes[i].mnemonic, retval);
    }
}