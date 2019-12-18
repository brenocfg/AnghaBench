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
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_N_BASECLASSES (struct type*) ; 

__attribute__((used)) static int
amd64_non_pod_p (struct type *type)
{
  /* ??? A class with a base class certainly isn't POD, but does this
     catch all non-POD structure types?  */
  if (TYPE_CODE (type) == TYPE_CODE_STRUCT && TYPE_N_BASECLASSES (type) > 0)
    return 1;

  return 0;
}