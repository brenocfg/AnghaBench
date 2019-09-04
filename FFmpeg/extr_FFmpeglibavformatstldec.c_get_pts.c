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
 int sscanf (char*,char*,int*,int*,int*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static int64_t get_pts(char **buf, int *duration)
{
    int hh1, mm1, ss1, ms1;
    int hh2, mm2, ss2, ms2;
    int len = 0;

    if (sscanf(*buf, "%2d:%2d:%2d:%2d , %2d:%2d:%2d:%2d , %n",
                &hh1, &mm1, &ss1, &ms1,
                &hh2, &mm2, &ss2, &ms2, &len) >= 8 && len > 0) {
        int64_t start = (hh1*3600LL + mm1*60LL + ss1) * 100LL + ms1;
        int64_t end = (hh2*3600LL + mm2*60LL + ss2) * 100LL + ms2;
        *duration = end - start;
        *buf += len;
        return start;
    }
    return AV_NOPTS_VALUE;
}