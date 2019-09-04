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

/* Variables and functions */
 int /*<<< orphan*/  __NEW_java_util_Locale () ; 
 int /*<<< orphan*/  java_util_Locale___INIT____java_lang_String_java_lang_String_java_lang_String (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_util_Locale_setDefault___java_util_Locale (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlvm_create_java_string (char*) ; 

void java_util_Locale_initNativeLayer__()
{
    //XMLVM_BEGIN_NATIVE[java_util_Locale_initNativeLayer__]
#ifdef __OBJC__
    NSUserDefaults* defs = [NSUserDefaults standardUserDefaults];
    NSArray* languages = [defs objectForKey:@"AppleLanguages"];
    NSString* language_ = [languages objectAtIndex:0];
    JAVA_OBJECT language = fromNSString(language_);
    JAVA_OBJECT country = xmlvm_create_java_string("US");
    JAVA_OBJECT variant = xmlvm_create_java_string("");
    JAVA_OBJECT defaultLocale = __NEW_java_util_Locale();
    java_util_Locale___INIT____java_lang_String_java_lang_String_java_lang_String(defaultLocale, language, country, variant);
    java_util_Locale_setDefault___java_util_Locale(defaultLocale);
#else
    //TODO we need a Posix implementation, this is just a dummy implementation
    JAVA_OBJECT language = xmlvm_create_java_string("en");
    JAVA_OBJECT country = xmlvm_create_java_string("US");
    JAVA_OBJECT variant = xmlvm_create_java_string("");
    JAVA_OBJECT defaultLocale = __NEW_java_util_Locale();
    java_util_Locale___INIT____java_lang_String_java_lang_String_java_lang_String(defaultLocale, language, country, variant);
    java_util_Locale_setDefault___java_util_Locale(defaultLocale);
#endif
    //XMLVM_END_NATIVE
}