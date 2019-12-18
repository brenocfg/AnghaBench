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
struct hdmi_spec {int /*<<< orphan*/  pcm_rec; int /*<<< orphan*/  cvts; int /*<<< orphan*/  pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_array_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdmi_array_free(struct hdmi_spec *spec)
{
	snd_array_free(&spec->pins);
	snd_array_free(&spec->cvts);
	snd_array_free(&spec->pcm_rec);
}