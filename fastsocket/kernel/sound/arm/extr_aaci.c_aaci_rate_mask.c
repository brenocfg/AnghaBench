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
struct aaci_stream {size_t codec_idx; size_t rate_idx; } ;
struct aaci {TYPE_2__* ac97_bus; } ;
struct TYPE_4__ {TYPE_1__** codec; } ;
struct TYPE_3__ {unsigned int* rates; } ;

/* Variables and functions */
 struct aaci_stream* aaci_streams ; 

__attribute__((used)) static inline unsigned int aaci_rate_mask(struct aaci *aaci, int streamid)
{
	struct aaci_stream *s = aaci_streams + streamid;
	return aaci->ac97_bus->codec[s->codec_idx]->rates[s->rate_idx];
}