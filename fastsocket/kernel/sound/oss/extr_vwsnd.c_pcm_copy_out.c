#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* swbuf; char* hwbuf; int sw_samplefmt; int swbuf_size; int hwbuf_size; } ;
typedef  TYPE_1__ vwsnd_port_t ;

/* Variables and functions */
 int AFMT_A_LAW ; 
 int AFMT_MU_LAW ; 
 int AFMT_S8 ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void pcm_copy_out(vwsnd_port_t *wport, int swidx, int hwidx, int nb)
{
	char *src = wport->swbuf + swidx;
	char *dst = wport->hwbuf + hwidx;
	int fmt = wport->sw_samplefmt;

	ASSERT(nb > 0 && (nb % 32) == 0);
	ASSERT(wport->hwbuf != NULL);
	ASSERT(wport->swbuf != NULL);
	ASSERT(swidx % 32 == 0 && hwidx % 32 == 0);
	ASSERT(swidx >= 0 && swidx + nb <= wport->swbuf_size);
	ASSERT(hwidx >= 0 && hwidx + nb <= wport->hwbuf_size);
	if (fmt == AFMT_MU_LAW || fmt == AFMT_A_LAW || fmt == AFMT_S8) {

		/* See Sample Format Notes above. */

		char *end = src + nb;
		while (src < end)
			*dst++ = *src++ ^ 0x80;
	} else
		memcpy(dst, src, nb);
}