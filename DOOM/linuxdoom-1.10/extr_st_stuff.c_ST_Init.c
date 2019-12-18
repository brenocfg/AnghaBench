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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  PU_STATIC ; 
 int ST_HEIGHT ; 
 int ST_WIDTH ; 
 int /*<<< orphan*/  ST_loadData () ; 
 scalar_t__ Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** screens ; 
 scalar_t__ veryfirsttime ; 

void ST_Init (void)
{
    veryfirsttime = 0;
    ST_loadData();
    screens[4] = (byte *) Z_Malloc(ST_WIDTH*ST_HEIGHT, PU_STATIC, 0);
}