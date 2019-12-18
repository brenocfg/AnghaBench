#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XPointer ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ XEvent ;
typedef  int /*<<< orphan*/  Display ;
typedef  int Bool ;

/* Variables and functions */
 scalar_t__ SelectionClear ; 
 scalar_t__ SelectionNotify ; 
 scalar_t__ SelectionRequest ; 

__attribute__((used)) static Bool isSelectionEvent(Display* display, XEvent* event, XPointer pointer)
{
    return event->type == SelectionRequest ||
           event->type == SelectionNotify ||
           event->type == SelectionClear;
}