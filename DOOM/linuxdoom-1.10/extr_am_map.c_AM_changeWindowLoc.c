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
struct TYPE_4__ {int /*<<< orphan*/  x; } ;
struct TYPE_3__ {scalar_t__ x; scalar_t__ y; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXINT ; 
 TYPE_2__ f_oldloc ; 
 scalar_t__ followplayer ; 
 int m_h ; 
 TYPE_1__ m_paninc ; 
 int m_w ; 
 scalar_t__ m_x ; 
 scalar_t__ m_x2 ; 
 scalar_t__ m_y ; 
 scalar_t__ m_y2 ; 
 scalar_t__ max_x ; 
 scalar_t__ max_y ; 
 scalar_t__ min_x ; 
 scalar_t__ min_y ; 

void AM_changeWindowLoc(void)
{
    if (m_paninc.x || m_paninc.y)
    {
	followplayer = 0;
	f_oldloc.x = MAXINT;
    }

    m_x += m_paninc.x;
    m_y += m_paninc.y;

    if (m_x + m_w/2 > max_x)
	m_x = max_x - m_w/2;
    else if (m_x + m_w/2 < min_x)
	m_x = min_x - m_w/2;
  
    if (m_y + m_h/2 > max_y)
	m_y = max_y - m_h/2;
    else if (m_y + m_h/2 < min_y)
	m_y = min_y - m_h/2;

    m_x2 = m_x + m_w;
    m_y2 = m_y + m_h;
}