#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  array_; } ;
struct TYPE_9__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_10__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_XMLVMArray ;
typedef  int jsize ;
typedef  TYPE_3__* JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_LONG ;
typedef  int JAVA_INT ;
typedef  int I_32 ;
typedef  int /*<<< orphan*/  IDATA ;

/* Variables and functions */
 int HyMaxPath ; 
 int HyOpenAppend ; 
 int HyOpenCreate ; 
 int HyOpenRead ; 
 int HyOpenSync ; 
 int HyOpenTruncate ; 
 int HyOpenWrite ; 
 int XMLVMArray_count (TYPE_3__*) ; 
 int /*<<< orphan*/  XMLVM_MEMCPY (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hyfile_open (char*,int,int) ; 
 int /*<<< orphan*/  ioh_convertToPlatform (char*) ; 
#define  org_apache_harmony_luni_platform_IFileSystem_O_APPEND 132 
#define  org_apache_harmony_luni_platform_IFileSystem_O_RDONLY 131 
#define  org_apache_harmony_luni_platform_IFileSystem_O_RDWR 130 
#define  org_apache_harmony_luni_platform_IFileSystem_O_RDWRSYNC 129 
#define  org_apache_harmony_luni_platform_IFileSystem_O_WRONLY 128 

JAVA_LONG org_apache_harmony_luni_platform_OSFileSystem_openImpl___byte_1ARRAY_int(JAVA_OBJECT me, JAVA_OBJECT n1, JAVA_INT n2)
{
    //XMLVM_BEGIN_NATIVE[org_apache_harmony_luni_platform_OSFileSystem_openImpl___byte_1ARRAY_int]
    org_xmlvm_runtime_XMLVMArray* path = n1;
    JAVA_INT jflags = n2;
    
    I_32 flags = 0;
    I_32 mode = 0; 
    IDATA portFD;
    jsize length;
    char pathCopy[HyMaxPath];
    
    switch(jflags){
        case org_apache_harmony_luni_platform_IFileSystem_O_RDONLY:
            flags = HyOpenRead;
            mode = 0;
            break;
        case org_apache_harmony_luni_platform_IFileSystem_O_WRONLY:
            flags = HyOpenCreate | HyOpenWrite | HyOpenTruncate;
            mode = 0666;
            break;
        case org_apache_harmony_luni_platform_IFileSystem_O_RDWR:
            flags = HyOpenRead | HyOpenWrite | HyOpenCreate;
            mode = 0666;
            break;
        case org_apache_harmony_luni_platform_IFileSystem_O_APPEND:
            flags = HyOpenWrite | HyOpenCreate | HyOpenAppend; 
            mode = 0666;
            break;
        case org_apache_harmony_luni_platform_IFileSystem_O_RDWRSYNC:
            flags = HyOpenRead | HyOpenWrite | HyOpenCreate | HyOpenSync;
            mode = 0666;
            break;
    }
    
    length = XMLVMArray_count(path);
    length = length < HyMaxPath - 1 ? length : HyMaxPath - 1;
    XMLVM_MEMCPY(pathCopy, path->fields.org_xmlvm_runtime_XMLVMArray.array_, length);
    pathCopy[length] = '\0';
    ioh_convertToPlatform (pathCopy);
    
    portFD = hyfile_open (pathCopy, flags, mode);
    return (JAVA_LONG) portFD;
    //XMLVM_END_NATIVE
}