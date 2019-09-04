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

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,char const*,int) ; 

void XMLVM_ERROR(const char* msg, const char* file, const char* function, int line)
{
    printf("XMLVM Error: %s: (%s):%s:%d\n", msg, function, file, line);
    exit(-1);
}