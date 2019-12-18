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
 int /*<<< orphan*/  C ; 
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  I ; 
 int /*<<< orphan*/  L ; 
 int /*<<< orphan*/  S ; 
 int c ; 
 int /*<<< orphan*/  d ; 
 int /*<<< orphan*/  f ; 
 int i ; 
 int /*<<< orphan*/  l ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s ; 

void print(void) {
	printf("%d %d %d %ld %u %u %u %lu %f %f %lf\n",c,s,i,l,C,S,I,L,f,d,D);
}