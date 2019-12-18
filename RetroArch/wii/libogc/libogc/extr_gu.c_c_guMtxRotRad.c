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
typedef  int /*<<< orphan*/  f32 ;
typedef  int /*<<< orphan*/  Mtx ;

/* Variables and functions */
 int /*<<< orphan*/  c_guMtxRotTrig (int /*<<< orphan*/ ,char const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cosf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sinf (int /*<<< orphan*/ ) ; 

void c_guMtxRotRad(Mtx mt,const char axis,f32 rad)
{
	f32 sinA,cosA;

	sinA = sinf(rad);
	cosA = cosf(rad);

	c_guMtxRotTrig(mt,axis,sinA,cosA);
}