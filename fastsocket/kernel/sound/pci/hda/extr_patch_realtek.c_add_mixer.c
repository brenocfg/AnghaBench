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
struct snd_kcontrol_new {int dummy; } ;
struct alc_spec {scalar_t__ num_mixers; struct snd_kcontrol_new const** mixers; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct snd_kcontrol_new const**) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static void add_mixer(struct alc_spec *spec, const struct snd_kcontrol_new *mix)
{
	if (snd_BUG_ON(spec->num_mixers >= ARRAY_SIZE(spec->mixers)))
		return;
	spec->mixers[spec->num_mixers++] = mix;
}