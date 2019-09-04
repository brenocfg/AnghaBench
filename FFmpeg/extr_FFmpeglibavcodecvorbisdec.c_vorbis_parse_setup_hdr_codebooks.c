#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int codebook_count; int /*<<< orphan*/ * avctx; TYPE_2__* codebooks; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ vorbis_context ;
struct TYPE_5__ {int dimensions; int lookup_type; float* codevectors; float maxdepth; int nb_bits; int /*<<< orphan*/  vlc; } ;
typedef  TYPE_2__ vorbis_codebook ;
typedef  float uint8_t ;
typedef  float uint32_t ;
typedef  float uint16_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  INIT_VLC_LE ; 
 int V_MAX_VLCS ; 
 int V_NB_BITS ; 
 int V_NB_BITS2 ; 
 int /*<<< orphan*/  av_free (float*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 float* av_malloc (int) ; 
 void* av_mallocz (int) ; 
 float* av_mallocz_array (unsigned int,int) ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ ff_vorbis_len2vlc (float*,float*,unsigned int) ; 
 unsigned int ff_vorbis_nth_root (unsigned int,int) ; 
 int get_bits (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits_long (int /*<<< orphan*/ *,int) ; 
 unsigned int ilog (unsigned int) ; 
 int init_vlc (int /*<<< orphan*/ *,int,unsigned int,float*,int,int,float*,int,int,int /*<<< orphan*/ ) ; 
 float vorbisfloat2float (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vorbis_parse_setup_hdr_codebooks(vorbis_context *vc)
{
    unsigned cb;
    uint8_t  *tmp_vlc_bits  = NULL;
    uint32_t *tmp_vlc_codes = NULL;
    GetBitContext *gb = &vc->gb;
    uint16_t *codebook_multiplicands = NULL;
    int ret = 0;

    vc->codebook_count = get_bits(gb, 8) + 1;

    ff_dlog(NULL, " Codebooks: %d \n", vc->codebook_count);

    vc->codebooks = av_mallocz(vc->codebook_count * sizeof(*vc->codebooks));
    tmp_vlc_bits  = av_mallocz(V_MAX_VLCS * sizeof(*tmp_vlc_bits));
    tmp_vlc_codes = av_mallocz(V_MAX_VLCS * sizeof(*tmp_vlc_codes));
    codebook_multiplicands = av_malloc(V_MAX_VLCS * sizeof(*codebook_multiplicands));
    if (!vc->codebooks ||
        !tmp_vlc_bits || !tmp_vlc_codes || !codebook_multiplicands) {
        ret = AVERROR(ENOMEM);
        goto error;
    }

    for (cb = 0; cb < vc->codebook_count; ++cb) {
        vorbis_codebook *codebook_setup = &vc->codebooks[cb];
        unsigned ordered, t, entries, used_entries = 0;

        ff_dlog(NULL, " %u. Codebook\n", cb);

        if (get_bits(gb, 24) != 0x564342) {
            av_log(vc->avctx, AV_LOG_ERROR,
                   " %u. Codebook setup data corrupt.\n", cb);
            ret = AVERROR_INVALIDDATA;
            goto error;
        }

        codebook_setup->dimensions=get_bits(gb, 16);
        if (codebook_setup->dimensions > 16 || codebook_setup->dimensions == 0) {
            av_log(vc->avctx, AV_LOG_ERROR,
                   " %u. Codebook's dimension is invalid (%d).\n",
                   cb, codebook_setup->dimensions);
            ret = AVERROR_INVALIDDATA;
            goto error;
        }
        entries = get_bits(gb, 24);
        if (entries > V_MAX_VLCS) {
            av_log(vc->avctx, AV_LOG_ERROR,
                   " %u. Codebook has too many entries (%u).\n",
                   cb, entries);
            ret = AVERROR_INVALIDDATA;
            goto error;
        }

        ordered = get_bits1(gb);

        ff_dlog(NULL, " codebook_dimensions %d, codebook_entries %u\n",
                codebook_setup->dimensions, entries);

        if (!ordered) {
            unsigned ce, flag;
            unsigned sparse = get_bits1(gb);

            ff_dlog(NULL, " not ordered \n");

            if (sparse) {
                ff_dlog(NULL, " sparse \n");

                used_entries = 0;
                for (ce = 0; ce < entries; ++ce) {
                    flag = get_bits1(gb);
                    if (flag) {
                        tmp_vlc_bits[ce] = get_bits(gb, 5) + 1;
                        ++used_entries;
                    } else
                        tmp_vlc_bits[ce] = 0;
                }
            } else {
                ff_dlog(NULL, " not sparse \n");

                used_entries = entries;
                for (ce = 0; ce < entries; ++ce)
                    tmp_vlc_bits[ce] = get_bits(gb, 5) + 1;
            }
        } else {
            unsigned current_entry  = 0;
            unsigned current_length = get_bits(gb, 5) + 1;

            ff_dlog(NULL, " ordered, current length: %u\n", current_length);  //FIXME

            used_entries = entries;
            for (; current_entry < used_entries && current_length <= 32; ++current_length) {
                unsigned i, number;

                ff_dlog(NULL, " number bits: %u ", ilog(entries - current_entry));

                number = get_bits(gb, ilog(entries - current_entry));

                ff_dlog(NULL, " number: %u\n", number);

                for (i = current_entry; i < number+current_entry; ++i)
                    if (i < used_entries)
                        tmp_vlc_bits[i] = current_length;

                current_entry+=number;
            }
            if (current_entry>used_entries) {
                av_log(vc->avctx, AV_LOG_ERROR, " More codelengths than codes in codebook. \n");
                ret = AVERROR_INVALIDDATA;
                goto error;
            }
        }

        codebook_setup->lookup_type = get_bits(gb, 4);

        ff_dlog(NULL, " lookup type: %d : %s \n", codebook_setup->lookup_type,
                codebook_setup->lookup_type ? "vq" : "no lookup");

// If the codebook is used for (inverse) VQ, calculate codevectors.

        if (codebook_setup->lookup_type == 1) {
            unsigned i, j, k;
            unsigned codebook_lookup_values = ff_vorbis_nth_root(entries, codebook_setup->dimensions);

            float codebook_minimum_value = vorbisfloat2float(get_bits_long(gb, 32));
            float codebook_delta_value   = vorbisfloat2float(get_bits_long(gb, 32));
            unsigned codebook_value_bits = get_bits(gb, 4) + 1;
            unsigned codebook_sequence_p = get_bits1(gb);

            ff_dlog(NULL, " We expect %d numbers for building the codevectors. \n",
                    codebook_lookup_values);
            ff_dlog(NULL, "  delta %f minmum %f \n",
                    codebook_delta_value, codebook_minimum_value);

            for (i = 0; i < codebook_lookup_values; ++i) {
                codebook_multiplicands[i] = get_bits(gb, codebook_value_bits);

                ff_dlog(NULL, " multiplicands*delta+minmum : %e \n",
                        (float)codebook_multiplicands[i] * codebook_delta_value + codebook_minimum_value);
                ff_dlog(NULL, " multiplicand %u\n", codebook_multiplicands[i]);
            }

// Weed out unused vlcs and build codevector vector
            if (used_entries) {
                codebook_setup->codevectors =
                    av_mallocz_array(used_entries, codebook_setup->dimensions *
                               sizeof(*codebook_setup->codevectors));
                if (!codebook_setup->codevectors) {
                    ret = AVERROR(ENOMEM);
                    goto error;
                }
            } else
                codebook_setup->codevectors = NULL;

            for (j = 0, i = 0; i < entries; ++i) {
                unsigned dim = codebook_setup->dimensions;

                if (tmp_vlc_bits[i]) {
                    float last = 0.0;
                    unsigned lookup_offset = i;

                    ff_dlog(vc->avctx, "Lookup offset %u ,", i);

                    for (k = 0; k < dim; ++k) {
                        unsigned multiplicand_offset = lookup_offset % codebook_lookup_values;
                        codebook_setup->codevectors[j * dim + k] = codebook_multiplicands[multiplicand_offset] * codebook_delta_value + codebook_minimum_value + last;
                        if (codebook_sequence_p)
                            last = codebook_setup->codevectors[j * dim + k];
                        lookup_offset/=codebook_lookup_values;
                    }
                    tmp_vlc_bits[j] = tmp_vlc_bits[i];

                    ff_dlog(vc->avctx, "real lookup offset %u, vector: ", j);
                    for (k = 0; k < dim; ++k)
                        ff_dlog(vc->avctx, " %f ",
                                codebook_setup->codevectors[j * dim + k]);
                    ff_dlog(vc->avctx, "\n");

                    ++j;
                }
            }
            if (j != used_entries) {
                av_log(vc->avctx, AV_LOG_ERROR, "Bug in codevector vector building code. \n");
                ret = AVERROR_INVALIDDATA;
                goto error;
            }
            entries = used_entries;
        } else if (codebook_setup->lookup_type >= 2) {
            av_log(vc->avctx, AV_LOG_ERROR, "Codebook lookup type not supported. \n");
            ret = AVERROR_INVALIDDATA;
            goto error;
        }

// Initialize VLC table
        if (ff_vorbis_len2vlc(tmp_vlc_bits, tmp_vlc_codes, entries)) {
            av_log(vc->avctx, AV_LOG_ERROR, " Invalid code lengths while generating vlcs. \n");
            ret = AVERROR_INVALIDDATA;
            goto error;
        }
        codebook_setup->maxdepth = 0;
        for (t = 0; t < entries; ++t)
            if (tmp_vlc_bits[t] >= codebook_setup->maxdepth)
                codebook_setup->maxdepth = tmp_vlc_bits[t];

        if (codebook_setup->maxdepth > 3 * V_NB_BITS)
            codebook_setup->nb_bits = V_NB_BITS2;
        else
            codebook_setup->nb_bits = V_NB_BITS;

        codebook_setup->maxdepth = (codebook_setup->maxdepth+codebook_setup->nb_bits - 1) / codebook_setup->nb_bits;

        if ((ret = init_vlc(&codebook_setup->vlc, codebook_setup->nb_bits,
                            entries, tmp_vlc_bits, sizeof(*tmp_vlc_bits),
                            sizeof(*tmp_vlc_bits), tmp_vlc_codes,
                            sizeof(*tmp_vlc_codes), sizeof(*tmp_vlc_codes),
                            INIT_VLC_LE))) {
            av_log(vc->avctx, AV_LOG_ERROR, " Error generating vlc tables. \n");
            goto error;
        }
    }

    av_free(tmp_vlc_bits);
    av_free(tmp_vlc_codes);
    av_free(codebook_multiplicands);
    return 0;

// Error:
error:
    av_free(tmp_vlc_bits);
    av_free(tmp_vlc_codes);
    av_free(codebook_multiplicands);
    return ret;
}