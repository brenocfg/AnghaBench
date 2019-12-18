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
struct TYPE_2__ {scalar_t__ next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_LEVEL ; 
 int /*<<< orphan*/  G_DoLoadLevel () ; 
 int /*<<< orphan*/  ga_nothing ; 
 int /*<<< orphan*/  gameaction ; 
 scalar_t__ gamemap ; 
 int /*<<< orphan*/  gamestate ; 
 int viewactive ; 
 TYPE_1__ wminfo ; 

void G_DoWorldDone (void) 
{        
    gamestate = GS_LEVEL; 
    gamemap = wminfo.next+1; 
    G_DoLoadLevel (); 
    gameaction = ga_nothing; 
    viewactive = true; 
}