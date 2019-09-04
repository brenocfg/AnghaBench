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
typedef  int JAVA_BOOLEAN ;

/* Variables and functions */
 char* XMLVMUtil_convertFromByteArray (int /*<<< orphan*/ ) ; 
 scalar_t__ remove (char*) ; 

JAVA_BOOLEAN java_io_File_deleteFileImpl___byte_1ARRAY(JAVA_OBJECT me, JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[java_io_File_deleteFileImpl___byte_1ARRAY]
    char* fileName = XMLVMUtil_convertFromByteArray(n1);
    return remove(fileName) == 0;
    //XMLVM_END_NATIVE
}