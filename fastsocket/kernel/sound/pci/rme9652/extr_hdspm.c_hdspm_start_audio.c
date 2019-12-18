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
struct hdspm {int control_register; } ;

/* Variables and functions */
 int HDSPM_AudioInterruptEnable ; 
 int HDSPM_Start ; 
 int /*<<< orphan*/  HDSPM_controlRegister ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void hdspm_start_audio(struct hdspm * s)
{
	s->control_register |= (HDSPM_AudioInterruptEnable | HDSPM_Start);
	hdspm_write(s, HDSPM_controlRegister, s->control_register);
}