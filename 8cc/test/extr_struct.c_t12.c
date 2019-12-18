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
struct tag12 {int a; int b; } ;

/* Variables and functions */
 int /*<<< orphan*/  expect (int,int) ; 

__attribute__((used)) static void t12() {
    struct tag12 a[3];
    a[0].a = 83;
    expect(83, a[0].a);
    a[0].b = 84;
    expect(84, a[0].b);
    a[1].b = 85;
    expect(85, a[1].b);
    int *p = (int *)a;
    expect(85, p[3]);
}