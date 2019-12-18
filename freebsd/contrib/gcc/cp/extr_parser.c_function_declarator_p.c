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
struct TYPE_3__ {scalar_t__ kind; struct TYPE_3__* declarator; } ;
typedef  TYPE_1__ cp_declarator ;

/* Variables and functions */
 scalar_t__ cdk_error ; 
 scalar_t__ cdk_function ; 
 scalar_t__ cdk_id ; 

__attribute__((used)) static bool
function_declarator_p (const cp_declarator *declarator)
{
  while (declarator)
    {
      if (declarator->kind == cdk_function
	  && declarator->declarator->kind == cdk_id)
	return true;
      if (declarator->kind == cdk_id
	  || declarator->kind == cdk_error)
	return false;
      declarator = declarator->declarator;
    }
  return false;
}