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
struct block {int dummy; } ;
struct TYPE_2__ {char const* scope; } ;

/* Variables and functions */
 TYPE_1__* BLOCK_NAMESPACE (struct block const*) ; 
 struct block* BLOCK_SUPERBLOCK (struct block const*) ; 

const char *
block_scope (const struct block *block)
{
  for (; block != NULL; block = BLOCK_SUPERBLOCK (block))
    {
      if (BLOCK_NAMESPACE (block) != NULL
	  && BLOCK_NAMESPACE (block)->scope != NULL)
	return BLOCK_NAMESPACE (block)->scope;
    }

  return "";
}