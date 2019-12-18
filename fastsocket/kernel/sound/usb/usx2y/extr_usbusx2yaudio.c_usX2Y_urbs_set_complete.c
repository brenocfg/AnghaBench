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
struct usX2Ydev {struct snd_usX2Y_substream** subs; } ;
struct urb {void (* complete ) (struct urb*) ;} ;
struct snd_usX2Y_substream {struct urb** urb; } ;

/* Variables and functions */
 int NRURBS ; 

__attribute__((used)) static void usX2Y_urbs_set_complete(struct usX2Ydev * usX2Y,
				    void (*complete)(struct urb *))
{
	int s, u;
	for (s = 0; s < 4; s++) {
		struct snd_usX2Y_substream *subs = usX2Y->subs[s];
		if (NULL != subs)
			for (u = 0; u < NRURBS; u++) {
				struct urb * urb = subs->urb[u];
				if (NULL != urb)
					urb->complete = complete;
			}
	}
}