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
 int /*<<< orphan*/  reverse (char*,char*) ; 
 int /*<<< orphan*/  swap (char,char) ; 

bool CalcAllPermutation(char* perm, int num){
	int i;

	//①找到排列中最后（最右）一个升序的首位位置i，x = ai
	for (i = num - 2; (i >= 0) && (perm[i] >= perm[i + 1]); --i){
		;
	}
	// 已经找到所有排列
	if (i < 0){
		return false;
	}

	int k;
	//②找到排列中第i位右边最后一个比ai 大的位置j，y = aj
	for (k = num - 1; (k > i) && (perm[k] <= perm[i]); --k){
		;
	}

	//③交换x，y
	swap(perm[i], perm[k]);
	//④把第(i+ 1)位到最后的部分翻转
	reverse(perm + i + 1, perm + num);
	return true;
}