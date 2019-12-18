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
 int /*<<< orphan*/  panicPutChar (int) ; 

__attribute__((used)) static void panicPutDec(int a)
{
    int n1, n2;
    n1 = a % 10;
    n2 = a / 10;
    if (n2 == 0) {
        panicPutChar(' ');
    } else {
        panicPutChar(n2 + '0');
    }
    panicPutChar(n1 + '0');
}