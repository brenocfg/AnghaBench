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
typedef  scalar_t__ JAVA_INT ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char) ; 

void org_xmlvm_runtime_XMLVMOutputStream_nativeWrite___int(JAVA_INT n1)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_XMLVMOutputStream_nativeWrite___int]
    printf("%c", (char) n1);
    //XMLVM_END_NATIVE
}