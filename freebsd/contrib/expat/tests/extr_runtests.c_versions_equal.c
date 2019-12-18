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
struct TYPE_4__ {scalar_t__ major; scalar_t__ minor; scalar_t__ micro; } ;
typedef  TYPE_1__ XML_Expat_Version ;

/* Variables and functions */

__attribute__((used)) static int
versions_equal(const XML_Expat_Version *first,
               const XML_Expat_Version *second)
{
    return (first->major == second->major &&
            first->minor == second->minor &&
            first->micro == second->micro);
}