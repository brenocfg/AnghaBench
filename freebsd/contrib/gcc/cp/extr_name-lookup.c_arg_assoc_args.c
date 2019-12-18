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
typedef  scalar_t__ tree ;
struct arg_lookup {int dummy; } ;

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ arg_assoc (struct arg_lookup*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
arg_assoc_args (struct arg_lookup *k, tree args)
{
  for (; args; args = TREE_CHAIN (args))
    if (arg_assoc (k, TREE_VALUE (args)))
      return true;
  return false;
}