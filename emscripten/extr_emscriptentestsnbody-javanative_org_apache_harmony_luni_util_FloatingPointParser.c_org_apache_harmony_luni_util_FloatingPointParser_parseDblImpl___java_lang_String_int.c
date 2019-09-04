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
typedef  scalar_t__ JAVA_INT ;
typedef  int JAVA_DOUBLE ;

/* Variables and functions */
 int atof (char const*) ; 
 int pow (int,scalar_t__) ; 
 char* xmlvm_java_string_to_const_char (int /*<<< orphan*/ ) ; 

JAVA_DOUBLE org_apache_harmony_luni_util_FloatingPointParser_parseDblImpl___java_lang_String_int(JAVA_OBJECT n1, JAVA_INT n2)
{
    //XMLVM_BEGIN_NATIVE[org_apache_harmony_luni_util_FloatingPointParser_parseDblImpl___java_lang_String_int]
    const char* doubleNumStr = xmlvm_java_string_to_const_char(n1);
    JAVA_DOUBLE doubleNum = atof(doubleNumStr);
    if (n2 == 0) {
        return doubleNum;
    }
    return doubleNum * pow(10, n2);
    //XMLVM_END_NATIVE
}