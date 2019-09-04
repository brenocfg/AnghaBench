#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ array_; } ;
struct TYPE_8__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_11__ {TYPE_2__ fields; } ;
typedef  TYPE_5__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_9__ {int slot_; } ;
struct TYPE_10__ {TYPE_3__ java_lang_reflect_Constructor; } ;
struct TYPE_12__ {TYPE_4__ fields; } ;
typedef  TYPE_6__ java_lang_reflect_Constructor ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_ARRAY_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVM_INTERNAL_ERROR () ; 
 scalar_t__ __NEW_org_apache_harmony_niochar_charset_UTF_8 () ; 
 int /*<<< orphan*/  org_apache_harmony_niochar_charset_UTF_8___INIT____java_lang_String_java_lang_String_1ARRAY (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static JAVA_OBJECT constructor_dispatcher(JAVA_OBJECT constructor, JAVA_OBJECT arguments)
{
    JAVA_OBJECT obj = __NEW_org_apache_harmony_niochar_charset_UTF_8();
    java_lang_reflect_Constructor* c = (java_lang_reflect_Constructor*) constructor;
    org_xmlvm_runtime_XMLVMArray* args = (org_xmlvm_runtime_XMLVMArray*) arguments;
    JAVA_ARRAY_OBJECT* argsArray = (JAVA_ARRAY_OBJECT*) args->fields.org_xmlvm_runtime_XMLVMArray.array_;
    switch (c->fields.java_lang_reflect_Constructor.slot_) {
    case 0:
        org_apache_harmony_niochar_charset_UTF_8___INIT____java_lang_String_java_lang_String_1ARRAY(obj, argsArray[0], argsArray[1]);
        break;
    default:
        XMLVM_INTERNAL_ERROR();
        break;
    }
    return obj;
}