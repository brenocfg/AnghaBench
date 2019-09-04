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
typedef  int /*<<< orphan*/  JAVA_INT ;

/* Variables and functions */
 int /*<<< orphan*/  towlower (int /*<<< orphan*/ ) ; 

JAVA_INT java_lang_String_toLowerCaseImpl___int(JAVA_OBJECT me, JAVA_INT n1)
{
    //XMLVM_BEGIN_NATIVE[java_lang_String_toLowerCaseImpl___int]
#ifdef __EMSCRIPTEN__
	return tolower(n1);
#else
    return towlower(n1);
#endif
    //XMLVM_END_NATIVE
}