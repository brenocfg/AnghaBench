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
typedef  int boolean_t ;
struct TYPE_3__ {scalar_t__ cputype; scalar_t__ is_final_image; } ;
typedef  TYPE_1__ KXLDObject ;

/* Variables and functions */
 scalar_t__ CPU_TYPE_ARM ; 
 scalar_t__ CPU_TYPE_ARM64 ; 
 scalar_t__ CPU_TYPE_X86_64 ; 

__attribute__((used)) static boolean_t
target_supports_protected_segments(const KXLDObject *object)
{
    return (object->is_final_image && 
            (object->cputype == CPU_TYPE_X86_64 ||
             object->cputype == CPU_TYPE_ARM ||
             object->cputype == CPU_TYPE_ARM64));
}