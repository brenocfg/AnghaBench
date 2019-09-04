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
typedef  int /*<<< orphan*/  JAVA_ARRAY_CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVMArray_createSingleDimensionWithData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLVM_ATOMIC_MALLOC (int) ; 
 int /*<<< orphan*/  __CLASS_char ; 
 int strlen (char const*) ; 

JAVA_OBJECT XMLVMArray_createFromString(const char* str)
{
    int len = strlen(str);
    int size = len * sizeof(JAVA_ARRAY_CHAR);
    int i;    
    JAVA_ARRAY_CHAR* data = XMLVM_ATOMIC_MALLOC(size);
    for (i = 0; i < len; i++) {
        data[i] = *str++;
    }
    return XMLVMArray_createSingleDimensionWithData(__CLASS_char, len, data);
}