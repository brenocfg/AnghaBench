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
typedef  int /*<<< orphan*/  java_nio_charset_CodingErrorAction ;
struct TYPE_4__ {int /*<<< orphan*/ * decoder_; int /*<<< orphan*/ * unmapAction_; int /*<<< orphan*/ * malformAction_; scalar_t__ finished_; scalar_t__ status_; int /*<<< orphan*/ * replace_; scalar_t__ maxBytes_; scalar_t__ averBytes_; int /*<<< orphan*/ * cs_; } ;
struct TYPE_5__ {TYPE_1__ java_nio_charset_CharsetEncoder; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_nio_charset_CharsetEncoder ;
typedef  int /*<<< orphan*/  java_nio_charset_CharsetDecoder ;
typedef  int /*<<< orphan*/  java_nio_charset_Charset ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_lang_Object (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_java_nio_charset_CharsetEncoder(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_lang_Object(me, 0 || derivedClassWillRegisterFinalizer);
    ((java_nio_charset_CharsetEncoder*) me)->fields.java_nio_charset_CharsetEncoder.cs_ = (java_nio_charset_Charset*) JAVA_NULL;
    ((java_nio_charset_CharsetEncoder*) me)->fields.java_nio_charset_CharsetEncoder.averBytes_ = 0;
    ((java_nio_charset_CharsetEncoder*) me)->fields.java_nio_charset_CharsetEncoder.maxBytes_ = 0;
    ((java_nio_charset_CharsetEncoder*) me)->fields.java_nio_charset_CharsetEncoder.replace_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    ((java_nio_charset_CharsetEncoder*) me)->fields.java_nio_charset_CharsetEncoder.status_ = 0;
    ((java_nio_charset_CharsetEncoder*) me)->fields.java_nio_charset_CharsetEncoder.finished_ = 0;
    ((java_nio_charset_CharsetEncoder*) me)->fields.java_nio_charset_CharsetEncoder.malformAction_ = (java_nio_charset_CodingErrorAction*) JAVA_NULL;
    ((java_nio_charset_CharsetEncoder*) me)->fields.java_nio_charset_CharsetEncoder.unmapAction_ = (java_nio_charset_CodingErrorAction*) JAVA_NULL;
    ((java_nio_charset_CharsetEncoder*) me)->fields.java_nio_charset_CharsetEncoder.decoder_ = (java_nio_charset_CharsetDecoder*) JAVA_NULL;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_nio_charset_CharsetEncoder]
    //XMLVM_END_WRAPPER
}