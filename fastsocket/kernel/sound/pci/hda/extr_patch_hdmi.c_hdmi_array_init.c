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
struct hdmi_spec_per_pin {int dummy; } ;
struct hdmi_spec_per_cvt {int dummy; } ;
struct hdmi_spec {int /*<<< orphan*/  pcm_rec; int /*<<< orphan*/  cvts; int /*<<< orphan*/  pins; } ;
struct hda_pcm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_array_init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void hdmi_array_init(struct hdmi_spec *spec, int nums)
{
	snd_array_init(&spec->pins, sizeof(struct hdmi_spec_per_pin), nums);
	snd_array_init(&spec->cvts, sizeof(struct hdmi_spec_per_cvt), nums);
	snd_array_init(&spec->pcm_rec, sizeof(struct hda_pcm), nums);
}