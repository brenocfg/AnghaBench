#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  o; } ;
typedef  TYPE_1__ XMLVMElem ;
typedef  int /*<<< orphan*/  JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  __NEW_org_xmlvm_runtime_XMLVMClassLoader () ; 
 int /*<<< orphan*/  org_xmlvm_runtime_XMLVMClassLoader___INIT___ (int /*<<< orphan*/ ) ; 

JAVA_OBJECT java_lang_Thread_getContextClassLoader__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Thread_getContextClassLoader__]
    XMLVMElem _r0;
    _r0.o = __NEW_org_xmlvm_runtime_XMLVMClassLoader();
    org_xmlvm_runtime_XMLVMClassLoader___INIT___(_r0.o);
    return _r0.o;
    //XMLVM_END_NATIVE
}