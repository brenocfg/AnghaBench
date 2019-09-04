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
typedef  int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray ;
typedef  int /*<<< orphan*/  java_lang_String ;
typedef  int /*<<< orphan*/  JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * XMLVMArray_createFromString (char const*) ; 
 int /*<<< orphan*/  XMLVMUtil_getFromStringPool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * __NEW_java_lang_String () ; 
 int /*<<< orphan*/  java_lang_String___INIT____char_1ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

JAVA_OBJECT xmlvm_create_java_string(const char* s)
{
    java_lang_String* str = __NEW_java_lang_String();
    org_xmlvm_runtime_XMLVMArray* charArray = XMLVMArray_createFromString(s);
    java_lang_String___INIT____char_1ARRAY(str, charArray);
    return XMLVMUtil_getFromStringPool(str);
}