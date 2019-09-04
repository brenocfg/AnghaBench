#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* tib; } ;
typedef  TYPE_2__ java_lang_Object ;
struct TYPE_9__ {int sizeInstance; } ;
typedef  TYPE_2__* JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVM_INTERNAL_ERROR () ; 
 TYPE_2__* XMLVM_MALLOC (int) ; 
 int /*<<< orphan*/  XMLVM_MEMCPY (TYPE_2__*,TYPE_2__*,int) ; 

JAVA_OBJECT java_lang_Object_clone__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Object_clone__]
    //TODO check for ImplementsClonable interface
    java_lang_Object* thiz = me;
    int sizeInstance = thiz->tib->sizeInstance;
    if (sizeInstance == -1) {
        XMLVM_INTERNAL_ERROR();
    }
    JAVA_OBJECT clone = XMLVM_MALLOC(sizeInstance);
    XMLVM_MEMCPY(clone, me, sizeInstance);
    return clone;
    //XMLVM_END_NATIVE
}