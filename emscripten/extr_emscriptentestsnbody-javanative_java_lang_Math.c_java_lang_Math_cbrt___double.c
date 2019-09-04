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
typedef  int /*<<< orphan*/  JAVA_DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  cbrt (int /*<<< orphan*/ ) ; 

JAVA_DOUBLE java_lang_Math_cbrt___double(JAVA_DOUBLE n1)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Math_cbrt___double]
    return cbrt(n1);
    //XMLVM_END_NATIVE
}