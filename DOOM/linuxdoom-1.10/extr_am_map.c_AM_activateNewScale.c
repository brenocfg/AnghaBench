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
 int FTOM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_h ; 
 int /*<<< orphan*/  f_w ; 
 int m_h ; 
 int m_w ; 
 scalar_t__ m_x ; 
 scalar_t__ m_x2 ; 
 scalar_t__ m_y ; 
 scalar_t__ m_y2 ; 

void AM_activateNewScale(void)
{
    m_x += m_w/2;
    m_y += m_h/2;
    m_w = FTOM(f_w);
    m_h = FTOM(f_h);
    m_x -= m_w/2;
    m_y -= m_h/2;
    m_x2 = m_x + m_w;
    m_y2 = m_y + m_h;
}