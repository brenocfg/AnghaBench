#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int submaps; int coupling_steps; int* magnitude; int* angle; int* mux; int* floor; int* residue; } ;
typedef  TYPE_2__ vorbis_enc_mapping ;
struct TYPE_7__ {int channels; int* log2_blocksize; int ncodebooks; int nfloors; int nresidues; int nmappings; int nmodes; TYPE_1__* modes; TYPE_2__* mappings; int /*<<< orphan*/ * residues; int /*<<< orphan*/ * floors; int /*<<< orphan*/ * codebooks; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_3__ vorbis_enc_context ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int blockflag; int mapping; } ;
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 int /*<<< orphan*/  av_xiphlacing (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int ilog (int) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_bits32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_codebook_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_floor_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_residue_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int put_main_header(vorbis_enc_context *venc, uint8_t **out)
{
    int i;
    PutBitContext pb;
    int len, hlens[3];
    int buffer_len = 50000;
    uint8_t *buffer = av_mallocz(buffer_len), *p = buffer;
    if (!buffer)
        return AVERROR(ENOMEM);

    // identification header
    init_put_bits(&pb, p, buffer_len);
    put_bits(&pb, 8, 1); //magic
    for (i = 0; "vorbis"[i]; i++)
        put_bits(&pb, 8, "vorbis"[i]);
    put_bits32(&pb, 0); // version
    put_bits(&pb,  8, venc->channels);
    put_bits32(&pb, venc->sample_rate);
    put_bits32(&pb, 0); // bitrate
    put_bits32(&pb, 0); // bitrate
    put_bits32(&pb, 0); // bitrate
    put_bits(&pb,  4, venc->log2_blocksize[0]);
    put_bits(&pb,  4, venc->log2_blocksize[1]);
    put_bits(&pb,  1, 1); // framing

    flush_put_bits(&pb);
    hlens[0] = put_bits_count(&pb) >> 3;
    buffer_len -= hlens[0];
    p += hlens[0];

    // comment header
    init_put_bits(&pb, p, buffer_len);
    put_bits(&pb, 8, 3); //magic
    for (i = 0; "vorbis"[i]; i++)
        put_bits(&pb, 8, "vorbis"[i]);
    put_bits32(&pb, 0); // vendor length TODO
    put_bits32(&pb, 0); // amount of comments
    put_bits(&pb,  1, 1); // framing

    flush_put_bits(&pb);
    hlens[1] = put_bits_count(&pb) >> 3;
    buffer_len -= hlens[1];
    p += hlens[1];

    // setup header
    init_put_bits(&pb, p, buffer_len);
    put_bits(&pb, 8, 5); //magic
    for (i = 0; "vorbis"[i]; i++)
        put_bits(&pb, 8, "vorbis"[i]);

    // codebooks
    put_bits(&pb, 8, venc->ncodebooks - 1);
    for (i = 0; i < venc->ncodebooks; i++)
        put_codebook_header(&pb, &venc->codebooks[i]);

    // time domain, reserved, zero
    put_bits(&pb,  6, 0);
    put_bits(&pb, 16, 0);

    // floors
    put_bits(&pb, 6, venc->nfloors - 1);
    for (i = 0; i < venc->nfloors; i++)
        put_floor_header(&pb, &venc->floors[i]);

    // residues
    put_bits(&pb, 6, venc->nresidues - 1);
    for (i = 0; i < venc->nresidues; i++)
        put_residue_header(&pb, &venc->residues[i]);

    // mappings
    put_bits(&pb, 6, venc->nmappings - 1);
    for (i = 0; i < venc->nmappings; i++) {
        vorbis_enc_mapping *mc = &venc->mappings[i];
        int j;
        put_bits(&pb, 16, 0); // mapping type

        put_bits(&pb, 1, mc->submaps > 1);
        if (mc->submaps > 1)
            put_bits(&pb, 4, mc->submaps - 1);

        put_bits(&pb, 1, !!mc->coupling_steps);
        if (mc->coupling_steps) {
            put_bits(&pb, 8, mc->coupling_steps - 1);
            for (j = 0; j < mc->coupling_steps; j++) {
                put_bits(&pb, ilog(venc->channels - 1), mc->magnitude[j]);
                put_bits(&pb, ilog(venc->channels - 1), mc->angle[j]);
            }
        }

        put_bits(&pb, 2, 0); // reserved

        if (mc->submaps > 1)
            for (j = 0; j < venc->channels; j++)
                put_bits(&pb, 4, mc->mux[j]);

        for (j = 0; j < mc->submaps; j++) {
            put_bits(&pb, 8, 0); // reserved time configuration
            put_bits(&pb, 8, mc->floor[j]);
            put_bits(&pb, 8, mc->residue[j]);
        }
    }

    // modes
    put_bits(&pb, 6, venc->nmodes - 1);
    for (i = 0; i < venc->nmodes; i++) {
        put_bits(&pb, 1, venc->modes[i].blockflag);
        put_bits(&pb, 16, 0); // reserved window type
        put_bits(&pb, 16, 0); // reserved transform type
        put_bits(&pb, 8, venc->modes[i].mapping);
    }

    put_bits(&pb, 1, 1); // framing

    flush_put_bits(&pb);
    hlens[2] = put_bits_count(&pb) >> 3;

    len = hlens[0] + hlens[1] + hlens[2];
    p = *out = av_mallocz(64 + len + len/255);
    if (!p)
        return AVERROR(ENOMEM);

    *p++ = 2;
    p += av_xiphlacing(p, hlens[0]);
    p += av_xiphlacing(p, hlens[1]);
    buffer_len = 0;
    for (i = 0; i < 3; i++) {
        memcpy(p, buffer + buffer_len, hlens[i]);
        p += hlens[i];
        buffer_len += hlens[i];
    }

    av_freep(&buffer);
    return p - *out;
}