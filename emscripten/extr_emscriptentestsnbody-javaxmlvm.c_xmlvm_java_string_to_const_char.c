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
struct TYPE_9__ {scalar_t__ array_; } ;
struct TYPE_10__ {TYPE_3__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_11__ {TYPE_4__ fields; } ;
typedef  TYPE_5__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_7__ {int count_; int offset_; scalar_t__ value_; } ;
struct TYPE_8__ {TYPE_1__ java_lang_String; } ;
struct TYPE_12__ {TYPE_2__ fields; } ;
typedef  TYPE_6__ java_lang_String ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  int JAVA_INT ;
typedef  char JAVA_ARRAY_CHAR ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 char* XMLVM_ATOMIC_MALLOC (int) ; 

const char* xmlvm_java_string_to_const_char(JAVA_OBJECT s)
{
    if (s == JAVA_NULL) {
        return "null";
    }
    java_lang_String* str = (java_lang_String*) s;
    JAVA_INT len = str->fields.java_lang_String.count_;
    char* cs = XMLVM_ATOMIC_MALLOC(len + 1);
    JAVA_INT offset = str->fields.java_lang_String.offset_;
    org_xmlvm_runtime_XMLVMArray* value = (org_xmlvm_runtime_XMLVMArray*) str->fields.java_lang_String.value_;
    JAVA_ARRAY_CHAR* valueArray = (JAVA_ARRAY_CHAR*) value->fields.org_xmlvm_runtime_XMLVMArray.array_;
    int i = 0;
    for (i = 0; i < len; i++) {
        cs[i] = valueArray[i + offset];
    }
    cs[i] = '\0';
    return cs;
}