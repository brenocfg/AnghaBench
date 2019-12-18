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
struct TYPE_3__ {int flags; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ cpp_hashnode ;

/* Variables and functions */
 int NODE_BUILTIN ; 
 int NODE_DISABLED ; 
 int /*<<< orphan*/  NT_VOID ; 

void
_cpp_free_definition (cpp_hashnode *h)
{
  /* Macros and assertions no longer have anything to free.  */
  h->type = NT_VOID;
  /* Clear builtin flag in case of redefinition.  */
  h->flags &= ~(NODE_BUILTIN | NODE_DISABLED);
}