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
typedef  int /*<<< orphan*/  java_lang_Class ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  int JAVA_BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/ * JAVA_NULL ; 
 int /*<<< orphan*/  XMLVM_THROW_WITH_CSTRING (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * java_lang_Class_getSuperclass__ (int /*<<< orphan*/ *) ; 
 scalar_t__ java_lang_Class_isPrimitive__ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  java_lang_NullPointerException ; 

JAVA_BOOLEAN java_lang_Class_isAssignableFrom___java_lang_Class(JAVA_OBJECT me, JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Class_isAssignableFrom___java_lang_Class]
    java_lang_Class* thiz = (java_lang_Class*) me;
    java_lang_Class* that = (java_lang_Class*) n1;
    
    // check parameters
    if (!that)
    {
        XMLVM_THROW_WITH_CSTRING(java_lang_NullPointerException, "fromClazz argument");
    }
    
    // if primitive class
    if (java_lang_Class_isPrimitive__(thiz))
        return thiz==that;
    
    // if non primitive
    java_lang_Class* compareTo=thiz;
    while(compareTo!=JAVA_NULL)
    {
        if (compareTo==that)
            return 1;
        compareTo = java_lang_Class_getSuperclass__(compareTo);
    }
    return 0;
    
    
    //XMLVM_END_NATIVE
}