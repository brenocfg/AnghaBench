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
 float INFINITY ; 
 float NAN ; 
 int /*<<< orphan*/  TestMax (float,float,float) ; 
 int /*<<< orphan*/  TestMin (float,float,float) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main()
{
	TestMin(-INFINITY, INFINITY, -INFINITY);
	TestMax(-INFINITY, INFINITY, INFINITY);

	TestMin(-INFINITY, 1.f, -INFINITY);
	TestMax(-INFINITY, 1.f, 1.f);

	TestMin(INFINITY, 1.f, 1.f);
	TestMax(INFINITY, 1.f, INFINITY);

	TestMin(-INFINITY, NAN, -INFINITY);
	TestMax(-INFINITY, NAN, -INFINITY);
	assert(Float2Int(0.0f) != Float2Int(-0.0f));

	if (NAN == NAN)
		printf("NAN == NAN\n");
	if (NAN != NAN)
		printf("NAN != NAN\n");
	TestMin(-0.0f, 0.0f, -0.0f);
	TestMax(-0.0f, 0.0f, 0.0f);
	printf("Success!\n");
}