#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length_; } ;
struct TYPE_5__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_XMLVMArray ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */

int XMLVMArray_count(JAVA_OBJECT array)
{
    org_xmlvm_runtime_XMLVMArray* a = (org_xmlvm_runtime_XMLVMArray*) array;
    return a->fields.org_xmlvm_runtime_XMLVMArray.length_;
}