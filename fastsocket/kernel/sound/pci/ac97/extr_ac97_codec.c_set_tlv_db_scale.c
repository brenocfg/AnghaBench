#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int const* p; } ;
struct snd_kcontrol {TYPE_2__* vd; TYPE_1__ tlv; } ;
struct TYPE_4__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_TLV_READ ; 

__attribute__((used)) static void set_tlv_db_scale(struct snd_kcontrol *kctl, const unsigned int *tlv)
{
	kctl->tlv.p = tlv;
	if (tlv)
		kctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_TLV_READ;
}