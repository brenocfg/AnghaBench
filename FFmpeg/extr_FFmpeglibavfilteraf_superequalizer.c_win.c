#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float iza; int /*<<< orphan*/  aa; } ;
typedef  TYPE_1__ SuperEqualizerContext ;

/* Variables and functions */
 int alpha (int /*<<< orphan*/ ) ; 
 float izero (TYPE_1__*,int) ; 
 int sqrtf (int) ; 

__attribute__((used)) static float win(SuperEqualizerContext *s, float n, int N)
{
    return izero(s, alpha(s->aa) * sqrtf(1 - 4 * n * n / ((N - 1) * (N - 1)))) / s->iza;
}