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
typedef  int JAVA_BOOLEAN ;

/* Variables and functions */

JAVA_BOOLEAN org_apache_harmony_luni_platform_OSMemory_isLittleEndianImpl__()
{
    //XMLVM_BEGIN_NATIVE[org_apache_harmony_luni_platform_OSMemory_isLittleEndianImpl__]
    struct {
        int  x;
        char c[sizeof(int)];
    } u;
    u.x = 1;
    return u.c[0] != 0;
    //XMLVM_END_NATIVE
}