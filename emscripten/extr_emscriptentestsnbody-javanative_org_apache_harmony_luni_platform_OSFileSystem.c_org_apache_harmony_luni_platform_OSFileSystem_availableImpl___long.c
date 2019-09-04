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
typedef  scalar_t__ JAVA_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  org_apache_harmony_luni_platform_IFileSystem_SEEK_CUR ; 
 int /*<<< orphan*/  org_apache_harmony_luni_platform_IFileSystem_SEEK_END ; 
 int /*<<< orphan*/  org_apache_harmony_luni_platform_IFileSystem_SEEK_SET ; 
 scalar_t__ org_apache_harmony_luni_platform_OSFileSystem_seekImpl___long_long_int (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

JAVA_LONG org_apache_harmony_luni_platform_OSFileSystem_availableImpl___long(JAVA_OBJECT me, JAVA_LONG n1)
{
    //XMLVM_BEGIN_NATIVE[org_apache_harmony_luni_platform_OSFileSystem_availableImpl___long]
    JAVA_OBJECT thiz = me;
    JAVA_LONG fd = n1;
    
    JAVA_LONG currentPosition = 
        org_apache_harmony_luni_platform_OSFileSystem_seekImpl___long_long_int(thiz, fd, 0, org_apache_harmony_luni_platform_IFileSystem_SEEK_CUR);
    
    JAVA_LONG endPosition =
        org_apache_harmony_luni_platform_OSFileSystem_seekImpl___long_long_int(thiz, fd, 0, org_apache_harmony_luni_platform_IFileSystem_SEEK_END);
    
    org_apache_harmony_luni_platform_OSFileSystem_seekImpl___long_long_int(thiz, fd, currentPosition, org_apache_harmony_luni_platform_IFileSystem_SEEK_SET);
    
    return (JAVA_LONG) (endPosition - currentPosition);
    //XMLVM_END_NATIVE
}