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
 int*** dp ; 
 int inf ; 
 scalar_t__ isValid (int,int,int,int) ; 

int getValue(int step, int x1, int x2, int n)  //处理越界 不存在的位置 给负无穷的值
{
	return isValid(step, x1, x2, n) ? dp[step % 2][x1][x2] : (-inf);
}