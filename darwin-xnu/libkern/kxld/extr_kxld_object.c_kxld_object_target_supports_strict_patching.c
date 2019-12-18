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
typedef  int boolean_t ;
struct TYPE_4__ {scalar_t__ cputype; } ;
typedef  TYPE_1__ KXLDObject ;

/* Variables and functions */
 scalar_t__ CPU_TYPE_I386 ; 
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 

boolean_t
kxld_object_target_supports_strict_patching(const KXLDObject *object)
{
    check(object);

    return (object->cputype != CPU_TYPE_I386);
}