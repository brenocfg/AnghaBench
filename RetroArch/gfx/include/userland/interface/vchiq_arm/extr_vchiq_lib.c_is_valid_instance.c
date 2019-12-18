#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* VCHIQ_INSTANCE_T ;
struct TYPE_4__ {scalar_t__ initialised; } ;

/* Variables and functions */
 TYPE_1__ vchiq_instance ; 

__attribute__((used)) static __inline int
is_valid_instance(VCHIQ_INSTANCE_T instance)
{
   return (instance == &vchiq_instance) && (instance->initialised > 0);
}