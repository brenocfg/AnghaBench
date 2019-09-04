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
 scalar_t__ check_ko (float*,float*) ; 
 int /*<<< orphan*/  copy_cpu (int,float*,int,float*,int) ; 
 int /*<<< orphan*/  move_go (float*,int,int,int) ; 
 scalar_t__ occupied (float*,int) ; 
 scalar_t__ suicide_go (float*,int,int,int) ; 

int legal_go(float *b, float *ko, int p, int r, int c)
{
    if (occupied(b, r*19+c)) return 0;
    float curr[19*19*3];
    copy_cpu(19*19*3, b, 1, curr, 1);
    move_go(curr, p, r, c);
    if(check_ko(curr, ko)) return 0;
    if(suicide_go(b, p, r, c)) return 0;
    return 1;
}