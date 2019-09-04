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
typedef  int /*<<< orphan*/  JAVA_LONG ;
typedef  int /*<<< orphan*/  JAVA_DOUBLE ;

/* Variables and functions */

JAVA_LONG java_lang_Double_doubleToLongBits___double(JAVA_DOUBLE n1)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Double_doubleToLongBits___double]
    union {
        JAVA_DOUBLE d;
        JAVA_LONG   l;
    } u;
    
    u.d = n1;
    return u.l;
    //XMLVM_END_NATIVE
}