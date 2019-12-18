#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int a; int b; int x; int y; int z; int c; } ;
struct TYPE_4__ {int a; int b; int c; } ;

/* Variables and functions */
 int /*<<< orphan*/  f2 (TYPE_2__*) ; 
 void* i ; 
 int /*<<< orphan*/  printf (char*,int,int,int,...) ; 
 TYPE_2__ x ; 
 TYPE_1__ y ; 

main()
{
	printf("x = %d %d %d %d %d %d\n", x.a, x.b, x.x, x.y, x.z, x.c);
	printf("y = %d %d %d\n", y.a, y.b, y.c);
	x.y = i;
	x.z = 070;
	printf("x = %d %d %d %d %d %d\n", x.a, x.b, x.x, x.y, x.z, x.c);
	y.a = 2;
	y.c = i;
	printf("y = %d %d %d\n", y.a, y.b, y.c);
	f2(&x);
	return 0;
}