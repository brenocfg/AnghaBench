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
struct TYPE_4__ {int /*<<< orphan*/ * this_0_; } ;
struct TYPE_5__ {TYPE_1__ org_apache_harmony_niochar_charset_UTF_8_Decoder; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_apache_harmony_niochar_charset_UTF_8_Decoder ;
typedef  int /*<<< orphan*/  org_apache_harmony_niochar_charset_UTF_8 ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_nio_charset_CharsetDecoder (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_org_apache_harmony_niochar_charset_UTF_8_Decoder(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_nio_charset_CharsetDecoder(me, 0 || derivedClassWillRegisterFinalizer);
    ((org_apache_harmony_niochar_charset_UTF_8_Decoder*) me)->fields.org_apache_harmony_niochar_charset_UTF_8_Decoder.this_0_ = (org_apache_harmony_niochar_charset_UTF_8*) JAVA_NULL;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_org_apache_harmony_niochar_charset_UTF_8_Decoder]
    //XMLVM_END_WRAPPER
}