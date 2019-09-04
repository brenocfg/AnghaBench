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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVM_INTERNAL_ERROR () ; 
 char* getcwd (char*,int) ; 
 int /*<<< orphan*/  xmlvm_create_java_string (char*) ; 

JAVA_OBJECT org_xmlvm_runtime_XMLVMUtil_getCurrentWorkingDirectory__()
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_XMLVMUtil_getCurrentWorkingDirectory__]
#ifdef __OBJC__
    // Base directory is <App>/Documents/
    // http://developer.apple.com/iphone/library/documentation/iPhone/Conceptual/iPhoneOSProgrammingGuide/FilesandNetworking/FilesandNetworking.html
    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString* path = [paths objectAtIndex:0];
    JAVA_OBJECT jpath = fromNSString(path);
    return jpath;
#else
    char buf[1024];
    char* err = getcwd(buf, sizeof(buf));
    if (err == NULL) {
        XMLVM_INTERNAL_ERROR();
    }
    return xmlvm_create_java_string(buf);
#endif
    //XMLVM_END_NATIVE
}