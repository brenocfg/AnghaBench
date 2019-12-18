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
typedef  int uint8_t ;

/* Variables and functions */
 int mid_pred (int,int,int) ; 

__attribute__((used)) static inline int loco_predict(uint8_t* data, int stride)
{
    int a, b, c;

    a = data[-stride];
    b = data[-1];
    c = data[-stride - 1];

    return mid_pred(a, a + b - c, b);
}