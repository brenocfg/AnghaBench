#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_13__ ;

/* Type definitions */
struct TYPE_25__ {int end_header; TYPE_2__* tp; TYPE_6__* packet; } ;
typedef  TYPE_3__ opj_tile_info_t ;
typedef  int /*<<< orphan*/  opj_tcd_tile_t ;
struct TYPE_26__ {TYPE_8__* cp; TYPE_7__* image; } ;
typedef  TYPE_4__ opj_t2_t ;
struct TYPE_27__ {scalar_t__ layno; size_t compno; int /*<<< orphan*/  resno; } ;
typedef  TYPE_5__ opj_pi_iterator_t ;
struct TYPE_28__ {int start_pos; int end_pos; int /*<<< orphan*/  end_ph_pos; } ;
typedef  TYPE_6__ opj_packet_info_t ;
struct TYPE_29__ {TYPE_1__* comps; } ;
typedef  TYPE_7__ opj_image_t ;
struct TYPE_30__ {scalar_t__ layer; scalar_t__ tp_on; TYPE_13__* tcps; } ;
typedef  TYPE_8__ opj_cp_t ;
struct TYPE_31__ {size_t packno; TYPE_3__* tile; } ;
typedef  TYPE_9__ opj_codestream_info_t ;
struct TYPE_24__ {int tp_numpacks; int tp_end_header; scalar_t__ tp_end_pos; } ;
struct TYPE_23__ {int /*<<< orphan*/  resno_decoded; } ;
struct TYPE_22__ {int numpocs; } ;

/* Variables and functions */
 int /*<<< orphan*/  int_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* pi_create_decode (TYPE_7__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  pi_destroy (TYPE_5__*,TYPE_8__*,int) ; 
 scalar_t__ pi_next (TYPE_5__*) ; 
 int t2_decode_packet (TYPE_4__*,unsigned char*,int,int /*<<< orphan*/ *,TYPE_13__*,TYPE_5__*,TYPE_6__*) ; 

int t2_decode_packets(opj_t2_t *t2, unsigned char *src, int len, int tileno, opj_tcd_tile_t *tile, opj_codestream_info_t *cstr_info) {
	unsigned char *c = src;
	opj_pi_iterator_t *pi;
	int pino, e = 0;
	int n = 0, curtp = 0;
	int tp_start_packno;

	opj_image_t *image = t2->image;
	opj_cp_t *cp = t2->cp;
	
	/* create a packet iterator */
	pi = pi_create_decode(image, cp, tileno);
	if(!pi) {
		/* TODO: throw an error */
		return -999;
	}

	tp_start_packno = 0;
	
	for (pino = 0; pino <= cp->tcps[tileno].numpocs; pino++) {
		while (pi_next(&pi[pino])) {
			if ((cp->layer==0) || (cp->layer>=((pi[pino].layno)+1))) {
				opj_packet_info_t *pack_info;
				if (cstr_info)
					pack_info = &cstr_info->tile[tileno].packet[cstr_info->packno];
				else
					pack_info = NULL;
				e = t2_decode_packet(t2, c, src + len - c, tile, &cp->tcps[tileno], &pi[pino], pack_info);
			} else {
				e = 0;
			}
			if(e == -999) return -999;
			/* progression in resolution */
			image->comps[pi[pino].compno].resno_decoded =	
				(e > 0) ? 
				int_max(pi[pino].resno, image->comps[pi[pino].compno].resno_decoded) 
				: image->comps[pi[pino].compno].resno_decoded;
			n++;

			/* INDEX >> */
			if(cstr_info) {
				opj_tile_info_t *info_TL = &cstr_info->tile[tileno];
				opj_packet_info_t *info_PK = &info_TL->packet[cstr_info->packno];
				if (!cstr_info->packno) {
					info_PK->start_pos = info_TL->end_header + 1;
				} else if (info_TL->packet[cstr_info->packno-1].end_pos >= (int)cstr_info->tile[tileno].tp[curtp].tp_end_pos){ // New tile part
					info_TL->tp[curtp].tp_numpacks = cstr_info->packno - tp_start_packno; // Number of packets in previous tile-part
					tp_start_packno = cstr_info->packno;
					curtp++;
					info_PK->start_pos = cstr_info->tile[tileno].tp[curtp].tp_end_header+1;
				} else {
					info_PK->start_pos = (cp->tp_on && info_PK->start_pos) ? info_PK->start_pos : info_TL->packet[cstr_info->packno - 1].end_pos + 1;
				}
				info_PK->end_pos = info_PK->start_pos + e - 1;
				info_PK->end_ph_pos += info_PK->start_pos - 1;	// End of packet header which now only represents the distance 
																												// to start of packet is incremented by value of start of packet
				cstr_info->packno++;
			}
			/* << INDEX */
			
			if (e == -999) {		/* ADD */
				break;
			} else {
				c += e;
			}			
		}
	}
	/* INDEX >> */
	if(cstr_info) {
		cstr_info->tile[tileno].tp[curtp].tp_numpacks = cstr_info->packno - tp_start_packno; // Number of packets in last tile-part
	}
	/* << INDEX */

	/* don't forget to release pi */
	pi_destroy(pi, cp, tileno);
	
	if (e == -999) {
		return e;
	}
	
	return (c - src);
}