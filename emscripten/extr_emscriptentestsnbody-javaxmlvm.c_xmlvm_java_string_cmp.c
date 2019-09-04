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
struct TYPE_9__ {scalar_t__ count_; scalar_t__ offset_; scalar_t__ value_; } ;
struct TYPE_10__ {TYPE_3__ java_lang_String; } ;
struct TYPE_12__ {TYPE_4__ fields; } ;
typedef  TYPE_6__ java_lang_String ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  scalar_t__ JAVA_INT ;
typedef  char const JAVA_ARRAY_CHAR ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 

int xmlvm_java_string_cmp(JAVA_OBJECT s1, const char* s2)
{
    java_lang_String* str = (java_lang_String*) s1;
    JAVA_INT len = str->fields.java_lang_String.count_;
    if (len != strlen(s2)) {
        return 0;
    }
    JAVA_INT offset = str->fields.java_lang_String.offset_;
    org_xmlvm_runtime_XMLVMArray* value = (org_xmlvm_runtime_XMLVMArray*) str->fields.java_lang_String.value_;
    JAVA_ARRAY_CHAR* valueArray = (JAVA_ARRAY_CHAR*) value->fields.org_xmlvm_runtime_XMLVMArray.array_;
    for (int i = 0; i < len; i++) {
        if (valueArray[i + offset] != s2[i]) {
            return 0;
        }
    }
    return 1;
}