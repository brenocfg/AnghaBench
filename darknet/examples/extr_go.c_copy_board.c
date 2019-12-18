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
 float* calloc (int,int) ; 
 int /*<<< orphan*/  copy_cpu (int,float*,int,float*,int) ; 

float *copy_board(float *board)
{
    float *next = calloc(19*19*3, sizeof(float));
    copy_cpu(19*19*3, board, 1, next, 1);
    return next;
}