#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int useAtomicMalloc; int sizeOfBaseType; } ;
typedef  TYPE_1__ TYPE_INFO ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_ARRAY_SHORT ;
typedef  int /*<<< orphan*/  JAVA_ARRAY_LONG ;
typedef  int /*<<< orphan*/  JAVA_ARRAY_INT ;
typedef  int /*<<< orphan*/  JAVA_ARRAY_FLOAT ;
typedef  int /*<<< orphan*/  JAVA_ARRAY_DOUBLE ;
typedef  int /*<<< orphan*/  JAVA_ARRAY_BYTE ;

/* Variables and functions */
 scalar_t__ __CLASS_boolean ; 
 scalar_t__ __CLASS_byte ; 
 scalar_t__ __CLASS_char ; 
 scalar_t__ __CLASS_double ; 
 scalar_t__ __CLASS_float ; 
 scalar_t__ __CLASS_int ; 
 scalar_t__ __CLASS_long ; 
 scalar_t__ __CLASS_short ; 

TYPE_INFO XMLVMArray_getTypeInfo(JAVA_OBJECT type)
{
    TYPE_INFO info;
    info.useAtomicMalloc = 1;
    
    if (type == __CLASS_byte || type == __CLASS_boolean) {
        info.sizeOfBaseType = sizeof(JAVA_ARRAY_BYTE);
    } else if (type == __CLASS_char || type == __CLASS_short) {
        info.sizeOfBaseType = sizeof(JAVA_ARRAY_SHORT);
    } else if (type == __CLASS_int) {
        info.sizeOfBaseType = sizeof(JAVA_ARRAY_INT);
    } else if (type == __CLASS_float) {
        info.sizeOfBaseType = sizeof(JAVA_ARRAY_FLOAT);
    } else if (type == __CLASS_double) {
        info.sizeOfBaseType = sizeof(JAVA_ARRAY_DOUBLE);
    } else if (type == __CLASS_long) {
        info.sizeOfBaseType = sizeof(JAVA_ARRAY_LONG);
    } else {
        info.sizeOfBaseType = sizeof(void*);
        // For arrays of object references we need to use the regular malloc() as the
        // GC needs to scan this memory region.
        info.useAtomicMalloc = 0;
    }
    
    return info;
}