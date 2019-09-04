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
 int /*<<< orphan*/  XMLVMArray_createSingleDimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __CLASS_java_lang_String ; 

JAVA_OBJECT java_lang_System_getPropertyList__()
{
    //XMLVM_BEGIN_NATIVE[java_lang_System_getPropertyList__]
    return XMLVMArray_createSingleDimension(__CLASS_java_lang_String, 0);
    //XMLVM_END_NATIVE
}