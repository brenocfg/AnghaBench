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
struct TYPE_3__ {int* p; int /*<<< orphan*/  (* c ) (struct snd_kcontrol*,int /*<<< orphan*/ ,int,int*) ;} ;
struct snd_kcontrol {TYPE_1__ tlv; TYPE_2__* vd; } ;
typedef  int /*<<< orphan*/  mm_segment_t ;
typedef  int /*<<< orphan*/  _tlv ;
struct TYPE_4__ {int access; } ;

/* Variables and functions */
 int SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK ; 
 int SNDRV_CTL_ELEM_ACCESS_TLV_READ ; 
 int const SNDRV_CTL_TLVT_DB_SCALE ; 
 int /*<<< orphan*/  get_ds () ; 
 int /*<<< orphan*/  get_fs () ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_kcontrol*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int get_kctl_0dB_offset(struct snd_kcontrol *kctl)
{
	int _tlv[4];
	const int *tlv = NULL;
	int val = -1;

	if (kctl->vd[0].access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) {
		/* FIXME: set_fs() hack for obtaining user-space TLV data */
		mm_segment_t fs = get_fs();
		set_fs(get_ds());
		if (!kctl->tlv.c(kctl, 0, sizeof(_tlv), _tlv))
			tlv = _tlv;
		set_fs(fs);
	} else if (kctl->vd[0].access & SNDRV_CTL_ELEM_ACCESS_TLV_READ)
		tlv = kctl->tlv.p;
	if (tlv && tlv[0] == SNDRV_CTL_TLVT_DB_SCALE)
		val = -tlv[2] / tlv[3];
	return val;
}