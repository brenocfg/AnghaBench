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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/ * basic_block ;
struct TYPE_2__ {int /*<<< orphan*/ * src; } ;

/* Variables and functions */
 scalar_t__ PHI_ARG_DEF (scalar_t__,int) ; 
 TYPE_1__* PHI_ARG_EDGE (scalar_t__,int) ; 
 int PHI_NUM_ARGS (scalar_t__) ; 

__attribute__((used)) static basic_block
find_bb_for_arg (tree phi, tree def)
{
  int i;
  bool foundone = false;
  basic_block result = NULL;
  for (i = 0; i < PHI_NUM_ARGS (phi); i++)
    if (PHI_ARG_DEF (phi, i) == def)
      {
	if (foundone)
	  return NULL;
	foundone = true;
	result = PHI_ARG_EDGE (phi, i)->src;
      }
  return result;
}