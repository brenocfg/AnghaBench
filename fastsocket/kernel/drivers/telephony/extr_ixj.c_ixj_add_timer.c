#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ expires; } ;
struct TYPE_4__ {TYPE_3__ timer; } ;
typedef  TYPE_1__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int hertz ; 
 scalar_t__ jiffies ; 
 int samplerate ; 

__attribute__((used)) static void ixj_add_timer(IXJ *j)
{
	j->timer.expires = jiffies + (hertz / samplerate);
	add_timer(&j->timer);
}