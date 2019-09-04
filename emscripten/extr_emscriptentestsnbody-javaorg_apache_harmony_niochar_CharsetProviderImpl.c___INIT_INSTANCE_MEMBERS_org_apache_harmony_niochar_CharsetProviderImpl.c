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
typedef  int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray ;
struct TYPE_5__ {int /*<<< orphan*/ * packageName_; int /*<<< orphan*/ * charsets_; int /*<<< orphan*/ * cache_; } ;
struct TYPE_4__ {TYPE_2__ org_apache_harmony_niochar_CharsetProviderImpl; } ;
struct TYPE_6__ {TYPE_1__ fields; } ;
typedef  TYPE_3__ org_apache_harmony_niochar_CharsetProviderImpl ;
typedef  int /*<<< orphan*/  java_util_Map ;
typedef  int /*<<< orphan*/  java_lang_String ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_nio_charset_spi_CharsetProvider (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_org_apache_harmony_niochar_CharsetProviderImpl(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_nio_charset_spi_CharsetProvider(me, 0 || derivedClassWillRegisterFinalizer);
    ((org_apache_harmony_niochar_CharsetProviderImpl*) me)->fields.org_apache_harmony_niochar_CharsetProviderImpl.cache_ = (java_util_Map*) JAVA_NULL;
    ((org_apache_harmony_niochar_CharsetProviderImpl*) me)->fields.org_apache_harmony_niochar_CharsetProviderImpl.charsets_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    ((org_apache_harmony_niochar_CharsetProviderImpl*) me)->fields.org_apache_harmony_niochar_CharsetProviderImpl.packageName_ = (java_lang_String*) JAVA_NULL;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_org_apache_harmony_niochar_CharsetProviderImpl]
    //XMLVM_END_WRAPPER
}