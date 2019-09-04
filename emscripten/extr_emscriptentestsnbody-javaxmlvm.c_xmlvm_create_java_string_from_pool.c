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
typedef  int /*<<< orphan*/ **** JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ ***** JAVA_NULL ; 
 int /*<<< orphan*/ * XMLVMArray_createSingleDimensionWithData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ****) ; 
 int /*<<< orphan*/ ****** XMLVMUtil_getFromStringPool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLVM_BZERO (int /*<<< orphan*/ *****,int) ; 
 int /*<<< orphan*/ ******* XMLVM_MALLOC (int) ; 
 int /*<<< orphan*/  __CLASS_char ; 
 int /*<<< orphan*/ * __NEW_java_lang_String () ; 
 int /*<<< orphan*/  java_lang_String___INIT____char_1ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ***** stringConstants ; 
 scalar_t__* xmlvm_constant_pool_data ; 
 int /*<<< orphan*/ * xmlvm_constant_pool_length ; 
 int xmlvm_constant_pool_size ; 

JAVA_OBJECT xmlvm_create_java_string_from_pool(int pool_id)
{
    if (stringConstants == JAVA_NULL) {
        // TODO: use XMLVM_ATOMIC_MALLOC?
        stringConstants = XMLVM_MALLOC(xmlvm_constant_pool_size * sizeof(JAVA_OBJECT));
        XMLVM_BZERO(stringConstants, xmlvm_constant_pool_size * sizeof(JAVA_OBJECT));
    }
    if (stringConstants[pool_id] != JAVA_NULL) {
        return stringConstants[pool_id];
    }
    java_lang_String* str = __NEW_java_lang_String();
    org_xmlvm_runtime_XMLVMArray* charArray = XMLVMArray_createSingleDimensionWithData(__CLASS_char,
                                                                                       xmlvm_constant_pool_length[pool_id],
                                                                                       (JAVA_OBJECT) xmlvm_constant_pool_data[pool_id]);
    java_lang_String___INIT____char_1ARRAY(str, charArray);
    JAVA_OBJECT poolStr = XMLVMUtil_getFromStringPool(str);
    stringConstants[pool_id] = poolStr;
    return poolStr;
}