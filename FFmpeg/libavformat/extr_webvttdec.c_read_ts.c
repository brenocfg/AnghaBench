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
 int AV_NOPTS_VALUE ; 
 int sscanf (char const*,char*,int*,int*,int*,...) ; 

__attribute__((used)) static int64_t read_ts(const char *s)
{
    int hh, mm, ss, ms;
    if (sscanf(s, "%u:%u:%u.%u", &hh, &mm, &ss, &ms) == 4) return (hh*3600LL + mm*60LL + ss) * 1000LL + ms;
    if (sscanf(s,    "%u:%u.%u",      &mm, &ss, &ms) == 3) return (            mm*60LL + ss) * 1000LL + ms;
    return AV_NOPTS_VALUE;
}