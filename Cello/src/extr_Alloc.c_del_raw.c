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
typedef  int /*<<< orphan*/  var ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_RAW ; 
 int /*<<< orphan*/  del_by (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void del_raw(var self) { del_by(self, ALLOC_RAW); }