#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* type_; } ;
struct TYPE_8__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_9__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_XMLVMArray ;
typedef  TYPE_3__* JAVA_OBJECT ;

/* Variables and functions */

JAVA_OBJECT org_xmlvm_runtime_XMLVMArray_getClass__(JAVA_OBJECT me)
{
    org_xmlvm_runtime_XMLVMArray* thiz = me;
    return thiz->fields.org_xmlvm_runtime_XMLVMArray.type_;
}