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
typedef  int uint64 ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64 GetCurTime(void)
{
 uint64 ret;
 struct timeval tv;

 gettimeofday(&tv,0);
 ret=(uint64)tv.tv_sec*1000000;
 ret+=tv.tv_usec;
 return(ret);
}