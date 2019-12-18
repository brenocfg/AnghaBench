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
struct obstack {int dummy; } ;
struct block {int dummy; } ;
struct TYPE_2__ {char const* scope; } ;

/* Variables and functions */
 TYPE_1__* BLOCK_NAMESPACE (struct block*) ; 
 int /*<<< orphan*/  block_initialize_namespace (struct block*,struct obstack*) ; 

void
block_set_scope (struct block *block, const char *scope,
		 struct obstack *obstack)
{
  block_initialize_namespace (block, obstack);

  BLOCK_NAMESPACE (block)->scope = scope;
}