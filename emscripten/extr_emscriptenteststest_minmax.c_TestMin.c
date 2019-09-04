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
 scalar_t__ Float2Int (float) ; 
 float Fminf (float,float) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,float,float,float,float) ; 

void TestMin(float a, float b, float ret)
{
	float x = Fminf(a, b);
	if (x != ret)
		printf("min(%f, %f) returned %f, should return ret: %f\n", a, b, x, ret);
	assert(Float2Int(x) == Float2Int(ret));
	float y = Fminf(b, a);
	if (y != ret)
		printf("min(%f, %f) returned %f, should return ret: %f\n", b, a, y, ret);
	assert(Float2Int(y) == Float2Int(ret));
}