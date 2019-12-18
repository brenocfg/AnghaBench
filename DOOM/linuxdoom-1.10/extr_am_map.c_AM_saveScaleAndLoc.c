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
 int /*<<< orphan*/  m_h ; 
 int /*<<< orphan*/  m_w ; 
 int /*<<< orphan*/  m_x ; 
 int /*<<< orphan*/  m_y ; 
 int /*<<< orphan*/  old_m_h ; 
 int /*<<< orphan*/  old_m_w ; 
 int /*<<< orphan*/  old_m_x ; 
 int /*<<< orphan*/  old_m_y ; 

void AM_saveScaleAndLoc(void)
{
    old_m_x = m_x;
    old_m_y = m_y;
    old_m_w = m_w;
    old_m_h = m_h;
}