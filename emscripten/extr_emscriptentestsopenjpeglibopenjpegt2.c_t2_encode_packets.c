#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int end_header; TYPE_6__* packet; } ;
typedef  TYPE_1__ opj_tile_info_t ;
struct TYPE_26__ {int POC; } ;
typedef  TYPE_2__ opj_tcp_t ;
struct TYPE_27__ {int /*<<< orphan*/  packno; } ;
typedef  TYPE_3__ opj_tcd_tile_t ;
struct TYPE_28__ {int /*<<< orphan*/  cinfo; TYPE_8__* cp; TYPE_7__* image; } ;
typedef  TYPE_4__ opj_t2_t ;
struct TYPE_29__ {int layno; } ;
typedef  TYPE_5__ opj_pi_iterator_t ;
struct TYPE_30__ {int start_pos; int end_pos; int /*<<< orphan*/  end_ph_pos; } ;
typedef  TYPE_6__ opj_packet_info_t ;
struct TYPE_31__ {int numcomps; } ;
typedef  TYPE_7__ opj_image_t ;
struct TYPE_32__ {scalar_t__ cinema; scalar_t__ max_comp_size; int tp_on; TYPE_2__* tcps; } ;
typedef  TYPE_8__ opj_cp_t ;
struct TYPE_33__ {size_t packno; TYPE_1__* tile; scalar_t__ index_write; } ;
typedef  TYPE_9__ opj_codestream_info_t ;
typedef  int /*<<< orphan*/  J2K_T2_MODE ;

/* Variables and functions */
 scalar_t__ CINEMA4K_24 ; 
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  THRESH_CALC ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pi_create_encode (TYPE_5__*,TYPE_8__*,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pi_destroy (TYPE_5__*,TYPE_8__*,int) ; 
 TYPE_5__* pi_initialise_encode (TYPE_7__*,TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pi_next (TYPE_5__*) ; 
 int t2_encode_packet (TYPE_3__*,TYPE_2__*,TYPE_5__*,unsigned char*,int,TYPE_9__*,int) ; 

int t2_encode_packets(opj_t2_t* t2,int tileno, opj_tcd_tile_t *tile, int maxlayers, unsigned char *dest, int len, opj_codestream_info_t *cstr_info,int tpnum, int tppos,int pino, J2K_T2_MODE t2_mode, int cur_totnum_tp){
	unsigned char *c = dest;
	int e = 0;
	int compno;
	opj_pi_iterator_t *pi = NULL;
	int poc;
	opj_image_t *image = t2->image;
	opj_cp_t *cp = t2->cp;
	opj_tcp_t *tcp = &cp->tcps[tileno];
	int pocno = cp->cinema == CINEMA4K_24? 2: 1;
	int maxcomp = cp->max_comp_size > 0 ? image->numcomps : 1;
	
	pi = pi_initialise_encode(image, cp, tileno, t2_mode);
	if(!pi) {
		/* TODO: throw an error */
		return -999;
	}
	
	if(t2_mode == THRESH_CALC ){ /* Calculating threshold */
		for(compno = 0; compno < maxcomp; compno++ ){
			for(poc = 0; poc < pocno ; poc++){
				int comp_len = 0;
				int tpnum = compno;
				if (pi_create_encode(pi, cp,tileno,poc,tpnum,tppos,t2_mode,cur_totnum_tp)) {
					opj_event_msg(t2->cinfo, EVT_ERROR, "Error initializing Packet Iterator\n");
					pi_destroy(pi, cp, tileno);
					return -999;
				}
				while (pi_next(&pi[poc])) {
					if (pi[poc].layno < maxlayers) {
						e = t2_encode_packet(tile, &cp->tcps[tileno], &pi[poc], c, dest + len - c, cstr_info, tileno);
						comp_len = comp_len + e;
						if (e == -999) {
							break;
						} else {
							c += e;
						}
					}
				}
				if (e == -999) break;
				if (cp->max_comp_size){
					if (comp_len > cp->max_comp_size){
						e = -999;
						break;
					}
				}
			}
			if (e == -999)  break;
		}
	}else{  /* t2_mode == FINAL_PASS  */
		pi_create_encode(pi, cp,tileno,pino,tpnum,tppos,t2_mode,cur_totnum_tp);
		while (pi_next(&pi[pino])) {
			if (pi[pino].layno < maxlayers) {
				e = t2_encode_packet(tile, &cp->tcps[tileno], &pi[pino], c, dest + len - c, cstr_info, tileno);
				if (e == -999) {
					break;
				} else {
					c += e;
				}
				/* INDEX >> */
				if(cstr_info) {
					if(cstr_info->index_write) {
						opj_tile_info_t *info_TL = &cstr_info->tile[tileno];
						opj_packet_info_t *info_PK = &info_TL->packet[cstr_info->packno];
						if (!cstr_info->packno) {
							info_PK->start_pos = info_TL->end_header + 1;
						} else {
							info_PK->start_pos = ((cp->tp_on | tcp->POC)&& info_PK->start_pos) ? info_PK->start_pos : info_TL->packet[cstr_info->packno - 1].end_pos + 1;
						}
						info_PK->end_pos = info_PK->start_pos + e - 1;
						info_PK->end_ph_pos += info_PK->start_pos - 1;	// End of packet header which now only represents the distance 
																														// to start of packet is incremented by value of start of packet
					}
					
					cstr_info->packno++;
				}
				/* << INDEX */
				tile->packno++;
			}
		}
	}
	
	pi_destroy(pi, cp, tileno);
	
	if (e == -999) {
		return e;
	}
	
  return (c - dest);
}