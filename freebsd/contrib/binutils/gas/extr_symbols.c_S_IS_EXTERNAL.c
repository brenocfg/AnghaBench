#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* bsym; } ;
typedef  TYPE_2__ symbolS ;
typedef  int flagword ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int BSF_GLOBAL ; 
 int BSF_LOCAL ; 
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_2__*) ; 
 int /*<<< orphan*/  abort () ; 

int
S_IS_EXTERNAL (symbolS *s)
{
  flagword flags;

  if (LOCAL_SYMBOL_CHECK (s))
    return 0;

  flags = s->bsym->flags;

  /* Sanity check.  */
  if ((flags & BSF_LOCAL) && (flags & BSF_GLOBAL))
    abort ();

  return (flags & BSF_GLOBAL) != 0;
}