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
 int CHARSETBUFF ; 
 int /*<<< orphan*/  getOSCharset (char*,int) ; 
 int /*<<< orphan*/  xmlvm_create_java_string (char*) ; 

JAVA_OBJECT java_lang_System_getEncoding___int(JAVA_INT n1)
{
    //XMLVM_BEGIN_NATIVE[java_lang_System_getEncoding___int]
    //Get charset from the OS
#ifdef __EMSCRIPTEN__
	return xmlvm_create_java_string("UTF-8");
#else
    char charset[CHARSETBUFF];
    getOSCharset(charset, CHARSETBUFF);
    return xmlvm_create_java_string(charset);
#endif
    //XMLVM_END_NATIVE
}