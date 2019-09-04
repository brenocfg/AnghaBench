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
typedef  int /*<<< orphan*/  JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVMArray_createSingleDimension (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XMLVMArray_fillArray (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __CLASS_java_lang_String ; 
 int /*<<< orphan*/  xmlvm_create_java_string (char const*) ; 

JAVA_OBJECT xmlvm_create_java_string_array(int count, const char **s) 
{
    JAVA_OBJECT javaStrings[count];
    for (int i = 0; i < count; i++) {
        javaStrings[i] = xmlvm_create_java_string(s[i]);
    }
    JAVA_OBJECT javaStringArray = XMLVMArray_createSingleDimension(__CLASS_java_lang_String, count);
    XMLVMArray_fillArray(javaStringArray, javaStrings);
    return javaStringArray;
}