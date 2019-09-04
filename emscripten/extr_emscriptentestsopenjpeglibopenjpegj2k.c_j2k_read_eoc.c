#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_tcd_t ;
struct TYPE_5__ {int state; int /*<<< orphan*/ ** tile_data; TYPE_2__* cp; int /*<<< orphan*/  cstr_info; int /*<<< orphan*/ * tile_len; int /*<<< orphan*/  image; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_1__ opj_j2k_t ;
struct TYPE_6__ {scalar_t__ limit_decoding; int tileno_size; int* tileno; } ;

/* Variables and functions */
 scalar_t__ DECODE_ALL_BUT_PACKETS ; 
 int J2K_STATE_ERR ; 
 int J2K_STATE_MT ; 
 int /*<<< orphan*/  opj_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tcd_create (int /*<<< orphan*/ ) ; 
 int tcd_decode_tile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcd_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcd_free_decode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcd_free_decode_tile (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcd_malloc_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  tcd_malloc_decode_tile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void j2k_read_eoc(opj_j2k_t *j2k) {
	int i, tileno;
	bool success;

	/* if packets should be decoded */
	if (j2k->cp->limit_decoding != DECODE_ALL_BUT_PACKETS) {
		opj_tcd_t *tcd = tcd_create(j2k->cinfo);
		tcd_malloc_decode(tcd, j2k->image, j2k->cp);
		for (i = 0; i < j2k->cp->tileno_size; i++) {
			tcd_malloc_decode_tile(tcd, j2k->image, j2k->cp, i, j2k->cstr_info);
			tileno = j2k->cp->tileno[i];
			success = tcd_decode_tile(tcd, j2k->tile_data[tileno], j2k->tile_len[tileno], tileno, j2k->cstr_info);
			opj_free(j2k->tile_data[tileno]);
			j2k->tile_data[tileno] = NULL;
			tcd_free_decode_tile(tcd, i);
			if (success == false) {
				j2k->state |= J2K_STATE_ERR;
				break;
			}
		}
		tcd_free_decode(tcd);
		tcd_destroy(tcd);
	}
	/* if packets should not be decoded  */
	else {
		for (i = 0; i < j2k->cp->tileno_size; i++) {
			tileno = j2k->cp->tileno[i];
			opj_free(j2k->tile_data[tileno]);
			j2k->tile_data[tileno] = NULL;
		}
	}	
	if (j2k->state & J2K_STATE_ERR)
		j2k->state = J2K_STATE_MT + J2K_STATE_ERR;
	else
		j2k->state = J2K_STATE_MT; 
}