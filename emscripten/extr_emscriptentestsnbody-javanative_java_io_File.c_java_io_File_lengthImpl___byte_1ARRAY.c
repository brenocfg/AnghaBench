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
typedef  int /*<<< orphan*/  JAVA_LONG ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 char* XMLVMUtil_convertFromByteArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 

JAVA_LONG java_io_File_lengthImpl___byte_1ARRAY(JAVA_OBJECT me, JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[java_io_File_lengthImpl___byte_1ARRAY]
    char* fileName = XMLVMUtil_convertFromByteArray(n1);
    FILE* fp = fopen(fileName, "rb");
    fseek(fp, 0L, SEEK_END);
    JAVA_LONG size = ftell(fp);
    fclose(fp);
    return size;
    //XMLVM_END_NATIVE
}