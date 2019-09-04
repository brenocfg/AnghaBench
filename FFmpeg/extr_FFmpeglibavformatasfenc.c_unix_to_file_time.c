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
typedef  int int64_t ;

/* Variables and functions */
 int INT64_C (int) ; 

__attribute__((used)) static int64_t unix_to_file_time(int64_t ti)
{
    int64_t t;

    t  = ti * INT64_C(10);
    t += INT64_C(116444736000000000);
    return t;
}