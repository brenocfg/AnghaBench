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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int JAVA_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

JAVA_LONG java_lang_System_currentTimeMillis__()
{
    //XMLVM_BEGIN_NATIVE[java_lang_System_currentTimeMillis__]
    struct timeval now;
    gettimeofday(&now, NULL);

    JAVA_LONG msec = ((JAVA_LONG) now.tv_sec) * 1000;
    msec += now.tv_usec / 1000;

    return msec;
    //XMLVM_END_NATIVE
}