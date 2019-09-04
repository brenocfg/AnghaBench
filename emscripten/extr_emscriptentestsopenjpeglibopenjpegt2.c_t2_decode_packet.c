#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int csty; int ppt; unsigned char* ppt_data; int ppt_len; TYPE_2__* tccps; } ;
typedef  TYPE_4__ opj_tcp_t ;
struct TYPE_30__ {TYPE_1__* comps; } ;
typedef  TYPE_5__ opj_tcd_tile_t ;
struct TYPE_31__ {scalar_t__ numpasses; scalar_t__ maxpasses; scalar_t__ numnewpasses; int newlen; unsigned char** data; int dataindex; int len; } ;
typedef  TYPE_6__ opj_tcd_seg_t ;
struct TYPE_32__ {int numbands; TYPE_10__* bands; } ;
typedef  TYPE_7__ opj_tcd_resolution_t ;
struct TYPE_28__ {TYPE_9__* dec; } ;
struct TYPE_33__ {int cw; int ch; TYPE_3__ cblks; int /*<<< orphan*/  imsbtree; int /*<<< orphan*/  incltree; } ;
typedef  TYPE_8__ opj_tcd_precinct_t ;
struct TYPE_34__ {int numsegs; int numnewpasses; int numlenbits; int len; unsigned char* data; TYPE_6__* segs; scalar_t__ numbps; } ;
typedef  TYPE_9__ opj_tcd_cblk_dec_t ;
struct TYPE_21__ {scalar_t__ x1; scalar_t__ x0; scalar_t__ y1; scalar_t__ y0; TYPE_8__* precincts; scalar_t__ numbps; } ;
typedef  TYPE_10__ opj_tcd_band_t ;
struct TYPE_22__ {int /*<<< orphan*/  cinfo; TYPE_14__* cp; } ;
typedef  TYPE_11__ opj_t2_t ;
struct TYPE_23__ {int compno; int resno; int precno; int layno; } ;
typedef  TYPE_12__ opj_pi_iterator_t ;
struct TYPE_24__ {int end_ph_pos; } ;
typedef  TYPE_13__ opj_packet_info_t ;
struct TYPE_25__ {int ppm; unsigned char* ppm_data; int ppm_len; } ;
typedef  TYPE_14__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_bio_t ;
struct TYPE_27__ {int /*<<< orphan*/  cblksty; } ;
struct TYPE_26__ {TYPE_7__* resolutions; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  EVT_WARNING ; 
 int J2K_CP_CSTY_EPH ; 
 int J2K_CP_CSTY_SOP ; 
 int /*<<< orphan*/ * bio_create () ; 
 int /*<<< orphan*/  bio_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_inalign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_init_dec (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  bio_numbytes (int /*<<< orphan*/ *) ; 
 void* bio_read (int /*<<< orphan*/ *,int) ; 
 int int_floorlog2 (scalar_t__) ; 
 scalar_t__ int_min (scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ opj_realloc (unsigned char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int t2_getcommacode (int /*<<< orphan*/ *) ; 
 int t2_getnumpasses (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t2_init_seg (TYPE_9__*,int,int /*<<< orphan*/ ,int) ; 
 int tgt_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tgt_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int t2_decode_packet(opj_t2_t* t2, unsigned char *src, int len, opj_tcd_tile_t *tile, 
														opj_tcp_t *tcp, opj_pi_iterator_t *pi, opj_packet_info_t *pack_info) {
	int bandno, cblkno;
	unsigned char *c = src;

	opj_cp_t *cp = t2->cp;

	int compno = pi->compno;	/* component value */
	int resno  = pi->resno;		/* resolution level value */
	int precno = pi->precno;	/* precinct value */
	int layno  = pi->layno;		/* quality layer value */

	opj_tcd_resolution_t* res = &tile->comps[compno].resolutions[resno];

	unsigned char *hd = NULL;
	int present;
	
	opj_bio_t *bio = NULL;	/* BIO component */
	
	if (layno == 0) {
		for (bandno = 0; bandno < res->numbands; bandno++) {
			opj_tcd_band_t *band = &res->bands[bandno];
			opj_tcd_precinct_t *prc = &band->precincts[precno];
			
			if ((band->x1-band->x0 == 0)||(band->y1-band->y0 == 0)) continue;
			
			tgt_reset(prc->incltree);
			tgt_reset(prc->imsbtree);
			for (cblkno = 0; cblkno < prc->cw * prc->ch; cblkno++) {
				opj_tcd_cblk_dec_t* cblk = &prc->cblks.dec[cblkno];
				cblk->numsegs = 0;
			}
		}
	}
	
	/* SOP markers */
	
	if (tcp->csty & J2K_CP_CSTY_SOP) {
		if ((*c) != 0xff || (*(c + 1) != 0x91)) {
			opj_event_msg(t2->cinfo, EVT_WARNING, "Expected SOP marker\n");
		} else {
			c += 6;
		}
		
		/** TODO : check the Nsop value */
	}
	
	/* 
	When the marker PPT/PPM is used the packet header are store in PPT/PPM marker
	This part deal with this caracteristic
	step 1: Read packet header in the saved structure
	step 2: Return to codestream for decoding 
	*/

	bio = bio_create();
	
	if (cp->ppm == 1) {		/* PPM */
		hd = cp->ppm_data;
		bio_init_dec(bio, hd, cp->ppm_len);
	} else if (tcp->ppt == 1) {	/* PPT */
		hd = tcp->ppt_data;
		bio_init_dec(bio, hd, tcp->ppt_len);
	} else {			/* Normal Case */
		hd = c;
		bio_init_dec(bio, hd, src+len-hd);
	}
	
	present = bio_read(bio, 1);
	
	if (!present) {
		bio_inalign(bio);
		hd += bio_numbytes(bio);
		bio_destroy(bio);
		
		/* EPH markers */
		
		if (tcp->csty & J2K_CP_CSTY_EPH) {
			if ((*hd) != 0xff || (*(hd + 1) != 0x92)) {
				printf("Error : expected EPH marker\n");
			} else {
				hd += 2;
			}
		}

		/* << INDEX */
		// End of packet header position. Currently only represents the distance to start of packet
		// Will be updated later by incrementing with packet start value
		if(pack_info) {
			pack_info->end_ph_pos = (int)(c - src);
		}
		/* INDEX >> */
		
		if (cp->ppm == 1) {		/* PPM case */
			cp->ppm_len += cp->ppm_data-hd;
			cp->ppm_data = hd;
			return (c - src);
		}
		if (tcp->ppt == 1) {	/* PPT case */
			tcp->ppt_len+=tcp->ppt_data-hd;
			tcp->ppt_data = hd;
			return (c - src);
		}
		
		return (hd - src);
	}
	
	for (bandno = 0; bandno < res->numbands; bandno++) {
		opj_tcd_band_t *band = &res->bands[bandno];
		opj_tcd_precinct_t *prc = &band->precincts[precno];
		
		if ((band->x1-band->x0 == 0)||(band->y1-band->y0 == 0)) continue;
		
		for (cblkno = 0; cblkno < prc->cw * prc->ch; cblkno++) {
			int included, increment, n, segno;
			opj_tcd_cblk_dec_t* cblk = &prc->cblks.dec[cblkno];
			/* if cblk not yet included before --> inclusion tagtree */
			if (!cblk->numsegs) {
				included = tgt_decode(bio, prc->incltree, cblkno, layno + 1);
				/* else one bit */
			} else {
				included = bio_read(bio, 1);
			}
			/* if cblk not included */
			if (!included) {
				cblk->numnewpasses = 0;
				continue;
			}
			/* if cblk not yet included --> zero-bitplane tagtree */
			if (!cblk->numsegs) {
				int i, numimsbs;
				for (i = 0; !tgt_decode(bio, prc->imsbtree, cblkno, i); i++) {
					;
				}
				numimsbs = i - 1;
				cblk->numbps = band->numbps - numimsbs;
				cblk->numlenbits = 3;
			}
			/* number of coding passes */
			cblk->numnewpasses = t2_getnumpasses(bio);
			increment = t2_getcommacode(bio);
			/* length indicator increment */
			cblk->numlenbits += increment;
			segno = 0;
			if (!cblk->numsegs) {
				t2_init_seg(cblk, segno, tcp->tccps[compno].cblksty, 1);
			} else {
				segno = cblk->numsegs - 1;
				if (cblk->segs[segno].numpasses == cblk->segs[segno].maxpasses) {
					++segno;
					t2_init_seg(cblk, segno, tcp->tccps[compno].cblksty, 0);
				}
			}
			n = cblk->numnewpasses;
			
			do {
				cblk->segs[segno].numnewpasses = int_min(cblk->segs[segno].maxpasses - cblk->segs[segno].numpasses, n);
				cblk->segs[segno].newlen = bio_read(bio, cblk->numlenbits + int_floorlog2(cblk->segs[segno].numnewpasses));
				n -= cblk->segs[segno].numnewpasses;
				if (n > 0) {
					++segno;
					t2_init_seg(cblk, segno, tcp->tccps[compno].cblksty, 0);
				}
			} while (n > 0);
		}
	}
	
	if (bio_inalign(bio)) {
		bio_destroy(bio);
		return -999;
	}
	
	hd += bio_numbytes(bio);
	bio_destroy(bio);
	
	/* EPH markers */
	if (tcp->csty & J2K_CP_CSTY_EPH) {
		if ((*hd) != 0xff || (*(hd + 1) != 0x92)) {
			opj_event_msg(t2->cinfo, EVT_ERROR, "Expected EPH marker\n");
			return -999;
		} else {
			hd += 2;
		}
	}

	/* << INDEX */
	// End of packet header position. Currently only represents the distance to start of packet
	// Will be updated later by incrementing with packet start value
	if(pack_info) {
		pack_info->end_ph_pos = (int)(hd - src);
	}
	/* INDEX >> */
	
	if (cp->ppm==1) {
		cp->ppm_len+=cp->ppm_data-hd;
		cp->ppm_data = hd;
	} else if (tcp->ppt == 1) {
		tcp->ppt_len+=tcp->ppt_data-hd;
		tcp->ppt_data = hd;
	} else {
		c=hd;
	}
	
	for (bandno = 0; bandno < res->numbands; bandno++) {
		opj_tcd_band_t *band = &res->bands[bandno];
		opj_tcd_precinct_t *prc = &band->precincts[precno];
		
		if ((band->x1-band->x0 == 0)||(band->y1-band->y0 == 0)) continue;
		
		for (cblkno = 0; cblkno < prc->cw * prc->ch; cblkno++) {
			opj_tcd_cblk_dec_t* cblk = &prc->cblks.dec[cblkno];
			opj_tcd_seg_t *seg = NULL;
			if (!cblk->numnewpasses)
				continue;
			if (!cblk->numsegs) {
				seg = &cblk->segs[0];
				cblk->numsegs++;
				cblk->len = 0;
			} else {
				seg = &cblk->segs[cblk->numsegs - 1];
				if (seg->numpasses == seg->maxpasses) {
					seg++;
					cblk->numsegs++;
				}
			}
			
			do {
				if (c + seg->newlen > src + len) {
					return -999;
				}

#ifdef USE_JPWL
			/* we need here a j2k handle to verify if making a check to
			the validity of cblocks parameters is selected from user (-W) */

				/* let's check that we are not exceeding */
				if ((cblk->len + seg->newlen) > 8192) {
					opj_event_msg(t2->cinfo, EVT_WARNING,
						"JPWL: segment too long (%d) for codeblock %d (p=%d, b=%d, r=%d, c=%d)\n",
						seg->newlen, cblkno, precno, bandno, resno, compno);
					if (!JPWL_ASSUME) {
						opj_event_msg(t2->cinfo, EVT_ERROR, "JPWL: giving up\n");
						return -999;
					}
					seg->newlen = 8192 - cblk->len;
					opj_event_msg(t2->cinfo, EVT_WARNING, "      - truncating segment to %d\n", seg->newlen);
					break;
				};

#endif /* USE_JPWL */
				
				cblk->data = (unsigned char*) opj_realloc(cblk->data, (cblk->len + seg->newlen) * sizeof(unsigned char*));
				memcpy(cblk->data + cblk->len, c, seg->newlen);
				if (seg->numpasses == 0) {
					seg->data = &cblk->data;
					seg->dataindex = cblk->len;
				}
				c += seg->newlen;
				cblk->len += seg->newlen;
				seg->len += seg->newlen;
				seg->numpasses += seg->numnewpasses;
				cblk->numnewpasses -= seg->numnewpasses;
				if (cblk->numnewpasses > 0) {
					seg++;
					cblk->numsegs++;
				}
			} while (cblk->numnewpasses > 0);
		}
	}
	
	return (c - src);
}