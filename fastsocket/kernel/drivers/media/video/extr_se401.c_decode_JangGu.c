#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_se401 {size_t curframe; int cwidth; int vlcdatapos; int* vlcdata; int cheight; TYPE_1__* frame; int /*<<< orphan*/  error; int /*<<< orphan*/  readcount; int /*<<< orphan*/  framecount; } ;
struct se401_scratch {unsigned char* data; int length; } ;
struct TYPE_2__ {int curpix; scalar_t__ grabstate; scalar_t__ data; scalar_t__ curline; scalar_t__ curlinepix; } ;

/* Variables and functions */
 scalar_t__ FRAME_DONE ; 
 scalar_t__ FRAME_GRABBING ; 
 scalar_t__ FRAME_READY ; 
 int SE401_NUMFRAMES ; 
 int /*<<< orphan*/  decode_JangGu_vlc (struct usb_se401*,int*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char*,int) ; 

__attribute__((used)) static inline void decode_JangGu(struct usb_se401 *se401,
						struct se401_scratch *buffer)
{
	unsigned char *data = buffer->data;
	int len = buffer->length;
	int bit_exp = 0, pix_exp = 0, frameinfo = 0, packetlength = 0, size;
	int datapos = 0;

	/* New image? */
	if (!se401->frame[se401->curframe].curpix) {
		se401->frame[se401->curframe].curlinepix = 0;
		se401->frame[se401->curframe].curline =
		    se401->frame[se401->curframe].data+
		    se401->cwidth * 3 - 1;
		if (se401->frame[se401->curframe].grabstate == FRAME_READY)
			se401->frame[se401->curframe].grabstate = FRAME_GRABBING;
		se401->vlcdatapos = 0;
	}
	while (datapos < len) {
		size = 1024 - se401->vlcdatapos;
		if (size+datapos > len)
			size = len-datapos;
		memcpy(se401->vlcdata+se401->vlcdatapos, data+datapos, size);
		se401->vlcdatapos += size;
		packetlength = 0;
		if (se401->vlcdatapos >= 4) {
			bit_exp = se401->vlcdata[3] + (se401->vlcdata[2] << 8);
			pix_exp = se401->vlcdata[1] +
					((se401->vlcdata[0] & 0x3f) << 8);
			frameinfo = se401->vlcdata[0] & 0xc0;
			packetlength = ((bit_exp + 47) >> 4) << 1;
			if (packetlength > 1024) {
				se401->vlcdatapos = 0;
				datapos = len;
				packetlength = 0;
				se401->error++;
				se401->frame[se401->curframe].curpix = 0;
			}
		}
		if (packetlength && se401->vlcdatapos >= packetlength) {
			decode_JangGu_vlc(se401, se401->vlcdata, bit_exp,
								packetlength);
			se401->frame[se401->curframe].curpix += pix_exp * 3;
			datapos += size-(se401->vlcdatapos-packetlength);
			se401->vlcdatapos = 0;
			if (se401->frame[se401->curframe].curpix >= se401->cwidth * se401->cheight * 3) {
				if (se401->frame[se401->curframe].curpix == se401->cwidth * se401->cheight * 3) {
					if (se401->frame[se401->curframe].grabstate == FRAME_GRABBING) {
						se401->frame[se401->curframe].grabstate = FRAME_DONE;
						se401->framecount++;
						se401->readcount++;
					}
					if (se401->frame[(se401->curframe + 1) & (SE401_NUMFRAMES - 1)].grabstate == FRAME_READY)
						se401->curframe = (se401->curframe + 1) & (SE401_NUMFRAMES - 1);
				} else
					se401->error++;
				se401->frame[se401->curframe].curpix = 0;
				datapos = len;
			}
		} else
			datapos += size;
	}
}