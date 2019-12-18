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
struct snd_array {int used; } ;
struct hda_pincfg {scalar_t__ nid; } ;
struct hda_codec {int dummy; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 struct hda_pincfg* snd_array_elem (struct snd_array*,int) ; 

__attribute__((used)) static struct hda_pincfg *look_up_pincfg(struct hda_codec *codec,
					 struct snd_array *array,
					 hda_nid_t nid)
{
	int i;
	for (i = 0; i < array->used; i++) {
		struct hda_pincfg *pin = snd_array_elem(array, i);
		if (pin->nid == nid)
			return pin;
	}
	return NULL;
}