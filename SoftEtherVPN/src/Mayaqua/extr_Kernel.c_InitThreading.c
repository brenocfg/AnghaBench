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
 int /*<<< orphan*/  NewCounter () ; 
 int /*<<< orphan*/  NewSk () ; 
 int /*<<< orphan*/  thread_count ; 
 int /*<<< orphan*/  thread_pool ; 

void InitThreading()
{
	thread_pool = NewSk();
	thread_count = NewCounter();
}