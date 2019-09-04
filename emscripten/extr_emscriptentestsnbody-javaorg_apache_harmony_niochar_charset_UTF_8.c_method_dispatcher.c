#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ array_; } ;
struct TYPE_9__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_12__ {TYPE_2__ fields; } ;
typedef  TYPE_5__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_10__ {int slot_; } ;
struct TYPE_11__ {TYPE_3__ java_lang_reflect_Method; } ;
struct TYPE_13__ {TYPE_4__ fields; } ;
typedef  TYPE_6__ java_lang_reflect_Method ;
typedef  int /*<<< orphan*/  java_lang_Object ;
struct TYPE_14__ {int /*<<< orphan*/  i; } ;
typedef  TYPE_7__ XMLVMElem ;
typedef  int /*<<< orphan*/ * JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_BOOLEAN ;
typedef  int /*<<< orphan*/  JAVA_ARRAY_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * JAVA_NULL ; 
 int /*<<< orphan*/  XMLVM_INTERNAL_ERROR () ; 
 int /*<<< orphan*/ * __NEW_java_lang_Boolean () ; 
 int /*<<< orphan*/  java_lang_Boolean___INIT____boolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  org_apache_harmony_niochar_charset_UTF_8_contains___java_nio_charset_Charset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  org_apache_harmony_niochar_charset_UTF_8_newDecoder__ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  org_apache_harmony_niochar_charset_UTF_8_newEncoder__ (int /*<<< orphan*/ *) ; 

__attribute__((used)) static JAVA_OBJECT method_dispatcher(JAVA_OBJECT method, JAVA_OBJECT receiver, JAVA_OBJECT arguments)
{
    JAVA_OBJECT result = JAVA_NULL;
    java_lang_Object* obj = receiver;
    java_lang_reflect_Method* m = (java_lang_reflect_Method*) method;
    org_xmlvm_runtime_XMLVMArray* args = (org_xmlvm_runtime_XMLVMArray*) arguments;
    JAVA_ARRAY_OBJECT* argsArray = (JAVA_ARRAY_OBJECT*) args->fields.org_xmlvm_runtime_XMLVMArray.array_;
    XMLVMElem conversion;
    switch (m->fields.java_lang_reflect_Method.slot_) {
    case 0:
        conversion.i = (JAVA_BOOLEAN) org_apache_harmony_niochar_charset_UTF_8_contains___java_nio_charset_Charset(receiver, argsArray[0]);
        result = __NEW_java_lang_Boolean();
        java_lang_Boolean___INIT____boolean(result, conversion.i);
        break;
    case 1:
        result = (JAVA_OBJECT) org_apache_harmony_niochar_charset_UTF_8_newDecoder__(receiver);
        break;
    case 2:
        result = (JAVA_OBJECT) org_apache_harmony_niochar_charset_UTF_8_newEncoder__(receiver);
        break;
    default:
        XMLVM_INTERNAL_ERROR();
        break;
    }
    return result;
}