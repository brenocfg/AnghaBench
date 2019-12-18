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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sclp_vt220_emit_current () ; 
 int sclp_vt220_flush_later ; 
 int /*<<< orphan*/  sclp_vt220_queue_running ; 

__attribute__((used)) static void
sclp_vt220_flush_chars(struct tty_struct *tty)
{
	if (!sclp_vt220_queue_running)
		sclp_vt220_emit_current();
	else
		sclp_vt220_flush_later = 1;
}