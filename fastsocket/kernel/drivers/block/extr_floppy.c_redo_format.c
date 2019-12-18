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
struct TYPE_2__ {int track; } ;

/* Variables and functions */
 int STRETCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _floppy ; 
 int buffer_track ; 
 int /*<<< orphan*/  debugt (char*) ; 
 int /*<<< orphan*/  floppy_start () ; 
 TYPE_1__ format_req ; 
 int /*<<< orphan*/  setup_format_params (int) ; 

__attribute__((used)) static void redo_format(void)
{
	buffer_track = -1;
	setup_format_params(format_req.track << STRETCH(_floppy));
	floppy_start();
	debugt("queue format request");
}