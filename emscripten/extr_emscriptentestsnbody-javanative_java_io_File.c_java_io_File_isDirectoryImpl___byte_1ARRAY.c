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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_BOOLEAN ;

/* Variables and functions */
 char* XMLVMUtil_convertFromByteArray (int /*<<< orphan*/ ) ; 
 int stat (char*,struct stat*) ; 

JAVA_BOOLEAN java_io_File_isDirectoryImpl___byte_1ARRAY(JAVA_OBJECT me, JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[java_io_File_isDirectoryImpl___byte_1ARRAY]
    char* fileName = XMLVMUtil_convertFromByteArray(n1);
    struct stat buf;
    int err;
    err = stat(fileName, &buf);
    return buf.st_mode; // XXX & S_IFDIR;
    //XMLVM_END_NATIVE
}