#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int classInitializationBegan; int classInitialized; int initializerThreadId; char const* className; int /*<<< orphan*/  vtable; int /*<<< orphan*/  flags; struct TYPE_3__* extends; } ;
typedef  TYPE_1__ __TIB_DEFINITION_TEMPLATE ;
struct TYPE_4__ {int /*<<< orphan*/  vtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVM_MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XMLVM_TYPE_PRIMITIVE ; 
 int /*<<< orphan*/  __TIB_java_lang_Class ; 
 TYPE_2__ __TIB_java_lang_Object ; 

void init_primitive_class(void* clazz, const char* name)
{
    __TIB_DEFINITION_TEMPLATE* c = (__TIB_DEFINITION_TEMPLATE*) clazz;
    //TODO who is initializing this class?
    c->classInitializationBegan = 1;
    c->classInitialized = 1;
    c->initializerThreadId = -1;
    c->className = name;
    c->extends = (__TIB_DEFINITION_TEMPLATE*) &__TIB_java_lang_Class;
    c->flags = XMLVM_TYPE_PRIMITIVE;
    XMLVM_MEMCPY(c->vtable, __TIB_java_lang_Object.vtable, sizeof(__TIB_java_lang_Object.vtable));
}