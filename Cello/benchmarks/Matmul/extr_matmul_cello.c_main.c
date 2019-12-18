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
typedef  int /*<<< orphan*/  var ;

/* Variables and functions */
 int /*<<< orphan*/  Matrix_Gen (int) ; 
 int /*<<< orphan*/  Matrix_Mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
	int n = 300;
	n = (n/2) * 2;
	var a = Matrix_Gen(n);
	var b = Matrix_Gen(n);
	var m = Matrix_Mul(a, b);
	del(a); del(b); del(m);
	return 0;
}