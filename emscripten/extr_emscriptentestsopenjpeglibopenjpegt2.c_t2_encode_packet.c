#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int csty; } ;
typedef  TYPE_3__ opj_tcp_t ;
struct TYPE_27__ {TYPE_6__* resolutions; } ;
typedef  TYPE_4__ opj_tcd_tilecomp_t ;
struct TYPE_28__ {int packno; TYPE_4__* comps; } ;
typedef  TYPE_5__ opj_tcd_tile_t ;
struct TYPE_29__ {int numbands; TYPE_11__* bands; } ;
typedef  TYPE_6__ opj_tcd_resolution_t ;
struct TYPE_24__ {TYPE_10__* enc; } ;
struct TYPE_30__ {int cw; int ch; TYPE_1__ cblks; int /*<<< orphan*/  imsbtree; int /*<<< orphan*/  incltree; } ;
typedef  TYPE_7__ opj_tcd_precinct_t ;
struct TYPE_31__ {scalar_t__ term; scalar_t__ len; } ;
typedef  TYPE_8__ opj_tcd_pass_t ;
struct TYPE_32__ {int numpasses; int len; scalar_t__ disto; int /*<<< orphan*/  data; } ;
typedef  TYPE_9__ opj_tcd_layer_t ;
struct TYPE_19__ {int numpasses; int numbps; int numlenbits; TYPE_9__* layers; TYPE_8__* passes; } ;
typedef  TYPE_10__ opj_tcd_cblk_enc_t ;
struct TYPE_20__ {int numbps; TYPE_7__* precincts; } ;
typedef  TYPE_11__ opj_tcd_band_t ;
struct TYPE_21__ {int compno; int resno; int precno; int layno; } ;
typedef  TYPE_12__ opj_pi_iterator_t ;
struct TYPE_22__ {int end_ph_pos; scalar_t__ disto; } ;
typedef  TYPE_13__ opj_packet_info_t ;
struct TYPE_23__ {size_t packno; scalar_t__ D_max; TYPE_2__* tile; scalar_t__ index_write; } ;
typedef  TYPE_14__ opj_codestream_info_t ;
typedef  int /*<<< orphan*/  opj_bio_t ;
struct TYPE_25__ {TYPE_13__* packet; } ;

/* Variables and functions */
 int J2K_CP_CSTY_EPH ; 
 int J2K_CP_CSTY_SOP ; 
 int /*<<< orphan*/ * bio_create () ; 
 int /*<<< orphan*/  bio_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_init_enc (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  bio_numbytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_write (int /*<<< orphan*/ *,int,int) ; 
 int int_floorlog2 (int) ; 
 int int_max (int,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t2_putcommacode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t2_putnumpasses (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tgt_encode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tgt_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgt_setvalue (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int t2_encode_packet(opj_tcd_tile_t * tile, opj_tcp_t * tcp, opj_pi_iterator_t *pi, unsigned char *dest, int length, opj_codestream_info_t *cstr_info, int tileno) {
	int bandno, cblkno;
	unsigned char *c = dest;

	int compno = pi->compno;	/* component value */
	int resno  = pi->resno;		/* resolution level value */
	int precno = pi->precno;	/* precinct value */
	int layno  = pi->layno;		/* quality layer value */

	opj_tcd_tilecomp_t *tilec = &tile->comps[compno];
	opj_tcd_resolution_t *res = &tilec->resolutions[resno];
	
	opj_bio_t *bio = NULL;	/* BIO component */
	
	/* <SOP 0xff91> */
	if (tcp->csty & J2K_CP_CSTY_SOP) {
		c[0] = 255;
		c[1] = 145;
		c[2] = 0;
		c[3] = 4;
		c[4] = (tile->packno % 65536) / 256;
		c[5] = (tile->packno % 65536) % 256;
		c += 6;
	}
	/* </SOP> */
	
	if (!layno) {
		for (bandno = 0; bandno < res->numbands; bandno++) {
			opj_tcd_band_t *band = &res->bands[bandno];
			opj_tcd_precinct_t *prc = &band->precincts[precno];
			tgt_reset(prc->incltree);
			tgt_reset(prc->imsbtree);
			for (cblkno = 0; cblkno < prc->cw * prc->ch; cblkno++) {
				opj_tcd_cblk_enc_t* cblk = &prc->cblks.enc[cblkno];
				cblk->numpasses = 0;
				tgt_setvalue(prc->imsbtree, cblkno, band->numbps - cblk->numbps);
			}
		}
	}
	
	bio = bio_create();
	bio_init_enc(bio, c, length);
	bio_write(bio, 1, 1);		/* Empty header bit */
	
	/* Writing Packet header */
	for (bandno = 0; bandno < res->numbands; bandno++) {
		opj_tcd_band_t *band = &res->bands[bandno];
		opj_tcd_precinct_t *prc = &band->precincts[precno];
		for (cblkno = 0; cblkno < prc->cw * prc->ch; cblkno++) {
			opj_tcd_cblk_enc_t* cblk = &prc->cblks.enc[cblkno];
			opj_tcd_layer_t *layer = &cblk->layers[layno];
			if (!cblk->numpasses && layer->numpasses) {
				tgt_setvalue(prc->incltree, cblkno, layno);
			}
		}
		for (cblkno = 0; cblkno < prc->cw * prc->ch; cblkno++) {
			opj_tcd_cblk_enc_t* cblk = &prc->cblks.enc[cblkno];
			opj_tcd_layer_t *layer = &cblk->layers[layno];
			int increment = 0;
			int nump = 0;
			int len = 0, passno;
			/* cblk inclusion bits */
			if (!cblk->numpasses) {
				tgt_encode(bio, prc->incltree, cblkno, layno + 1);
			} else {
				bio_write(bio, layer->numpasses != 0, 1);
			}
			/* if cblk not included, go to the next cblk  */
			if (!layer->numpasses) {
				continue;
			}
			/* if first instance of cblk --> zero bit-planes information */
			if (!cblk->numpasses) {
				cblk->numlenbits = 3;
				tgt_encode(bio, prc->imsbtree, cblkno, 999);
			}
			/* number of coding passes included */
			t2_putnumpasses(bio, layer->numpasses);
			
			/* computation of the increase of the length indicator and insertion in the header     */
			for (passno = cblk->numpasses; passno < cblk->numpasses + layer->numpasses; passno++) {
				opj_tcd_pass_t *pass = &cblk->passes[passno];
				nump++;
				len += pass->len;
				if (pass->term || passno == (cblk->numpasses + layer->numpasses) - 1) {
					increment = int_max(increment, int_floorlog2(len) + 1 - (cblk->numlenbits + int_floorlog2(nump)));
					len = 0;
					nump = 0;
				}
			}
			t2_putcommacode(bio, increment);

			/* computation of the new Length indicator */
			cblk->numlenbits += increment;

			/* insertion of the codeword segment length */
			for (passno = cblk->numpasses; passno < cblk->numpasses + layer->numpasses; passno++) {
				opj_tcd_pass_t *pass = &cblk->passes[passno];
				nump++;
				len += pass->len;
				if (pass->term || passno == (cblk->numpasses + layer->numpasses) - 1) {
					bio_write(bio, len, cblk->numlenbits + int_floorlog2(nump));
					len = 0;
					nump = 0;
				}
			}
		}
	}

	if (bio_flush(bio)) {
		bio_destroy(bio);
		return -999;		/* modified to eliminate longjmp !! */
	}

	c += bio_numbytes(bio);
	bio_destroy(bio);
	
	/* <EPH 0xff92> */
	if (tcp->csty & J2K_CP_CSTY_EPH) {
		c[0] = 255;
		c[1] = 146;
		c += 2;
	}
	/* </EPH> */

	/* << INDEX */
	// End of packet header position. Currently only represents the distance to start of packet
	// Will be updated later by incrementing with packet start value
	if(cstr_info && cstr_info->index_write) {
		opj_packet_info_t *info_PK = &cstr_info->tile[tileno].packet[cstr_info->packno];
		info_PK->end_ph_pos = (int)(c - dest);
	}
	/* INDEX >> */
	
	/* Writing the packet body */
	
	for (bandno = 0; bandno < res->numbands; bandno++) {
		opj_tcd_band_t *band = &res->bands[bandno];
		opj_tcd_precinct_t *prc = &band->precincts[precno];
		for (cblkno = 0; cblkno < prc->cw * prc->ch; cblkno++) {
			opj_tcd_cblk_enc_t* cblk = &prc->cblks.enc[cblkno];
			opj_tcd_layer_t *layer = &cblk->layers[layno];
			if (!layer->numpasses) {
				continue;
			}
			if (c + layer->len > dest + length) {
				return -999;
			}
			
			memcpy(c, layer->data, layer->len);
			cblk->numpasses += layer->numpasses;
			c += layer->len;
			/* << INDEX */ 
			if(cstr_info && cstr_info->index_write) {
				opj_packet_info_t *info_PK = &cstr_info->tile[tileno].packet[cstr_info->packno];
				info_PK->disto += layer->disto;
				if (cstr_info->D_max < info_PK->disto) {
					cstr_info->D_max = info_PK->disto;
				}
			}
			/* INDEX >> */
		}
	}
	
	return (c - dest);
}