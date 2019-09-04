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

JAVA_OBJECT java_io_File_getCanonImpl___byte_1ARRAY(JAVA_OBJECT me, JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[java_io_File_getCanonImpl___byte_1ARRAY]
    //See HARMONY/classlib/modules/luni/src/main/native/luni/shared/file.c
    //They don't seem to do more either on a UNIX file system
    return n1;
    //XMLVM_END_NATIVE
}