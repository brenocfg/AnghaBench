#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* mo; } ;
struct TYPE_3__ {scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int FRACBITS ; 
 int FRACUNIT ; 
 void* FixedDiv (int,int) ; 
 int f_w ; 
 int /*<<< orphan*/  followplayer ; 
 int m_h ; 
 int m_w ; 
 scalar_t__ m_x ; 
 scalar_t__ m_x2 ; 
 scalar_t__ m_y ; 
 scalar_t__ m_y2 ; 
 int old_m_h ; 
 int old_m_w ; 
 scalar_t__ old_m_x ; 
 scalar_t__ old_m_y ; 
 TYPE_2__* plr ; 
 void* scale_ftom ; 
 int scale_mtof ; 

void AM_restoreScaleAndLoc(void)
{

    m_w = old_m_w;
    m_h = old_m_h;
    if (!followplayer)
    {
	m_x = old_m_x;
	m_y = old_m_y;
    } else {
	m_x = plr->mo->x - m_w/2;
	m_y = plr->mo->y - m_h/2;
    }
    m_x2 = m_x + m_w;
    m_y2 = m_y + m_h;

    // Change the scaling multipliers
    scale_mtof = FixedDiv(f_w<<FRACBITS, m_w);
    scale_ftom = FixedDiv(FRACUNIT, scale_mtof);
}