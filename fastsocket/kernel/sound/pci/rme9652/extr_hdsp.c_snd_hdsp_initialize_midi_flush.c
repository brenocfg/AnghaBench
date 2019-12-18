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
struct hdsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hdsp_flush_midi_input (struct hdsp*,int) ; 

__attribute__((used)) static void snd_hdsp_initialize_midi_flush (struct hdsp *hdsp)
{
	snd_hdsp_flush_midi_input (hdsp, 0);
	snd_hdsp_flush_midi_input (hdsp, 1);
}