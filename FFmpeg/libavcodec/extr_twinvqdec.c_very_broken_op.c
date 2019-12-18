#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int size; int* tab; } ;

/* Variables and functions */
 int av_log2 (int) ; 
 TYPE_1__* tabs ; 

__attribute__((used)) static int very_broken_op(int a, int b)
{
    int x = a * b + 200;
    int size;
    const uint8_t *rtab;

    if (x % 400 || b % 5)
        return x / 400;

    x /= 400;

    size = tabs[b / 5].size;
    rtab = tabs[b / 5].tab;
    return x - rtab[size * av_log2(2 * (x - 1) / size) + (x - 1) % size];
}