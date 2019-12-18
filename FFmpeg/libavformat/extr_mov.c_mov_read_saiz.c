#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  fc; } ;
struct TYPE_16__ {int auxiliary_info_sample_count; scalar_t__ auxiliary_info_default_size; scalar_t__ auxiliary_offsets_count; int /*<<< orphan*/  auxiliary_info_sizes; scalar_t__ nb_encrypted_samples; } ;
struct TYPE_14__ {TYPE_1__* default_encrypted_sample; } ;
struct TYPE_15__ {TYPE_2__ cenc; } ;
struct TYPE_13__ {unsigned int scheme; } ;
typedef  TYPE_3__ MOVStreamContext ;
typedef  TYPE_4__ MOVEncryptionIndex ;
typedef  TYPE_5__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 unsigned int MKBETAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb24 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rb32 (int /*<<< orphan*/ *) ; 
 int get_current_encryption_info (TYPE_5__*,TYPE_4__**,TYPE_3__**) ; 
 int mov_parse_auxiliary_info (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int mov_try_read_block (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mov_read_saiz(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    MOVEncryptionIndex *encryption_index;
    MOVStreamContext *sc;
    int ret;
    unsigned int sample_count, aux_info_type, aux_info_param;

    ret = get_current_encryption_info(c, &encryption_index, &sc);
    if (ret != 1)
        return ret;

    if (encryption_index->nb_encrypted_samples) {
        // This can happen if we have both saio/saiz and senc atoms.
        av_log(c->fc, AV_LOG_DEBUG, "Ignoring duplicate encryption info in saiz\n");
        return 0;
    }

    if (encryption_index->auxiliary_info_sample_count) {
        av_log(c->fc, AV_LOG_ERROR, "Duplicate saiz atom\n");
        return AVERROR_INVALIDDATA;
    }

    avio_r8(pb); /* version */
    if (avio_rb24(pb) & 0x01) {  /* flags */
        aux_info_type = avio_rb32(pb);
        aux_info_param = avio_rb32(pb);
        if (sc->cenc.default_encrypted_sample) {
            if (aux_info_type != sc->cenc.default_encrypted_sample->scheme) {
                av_log(c->fc, AV_LOG_DEBUG, "Ignoring saiz box with non-zero aux_info_type\n");
                return 0;
            }
            if (aux_info_param != 0) {
                av_log(c->fc, AV_LOG_DEBUG, "Ignoring saiz box with non-zero aux_info_type_parameter\n");
                return 0;
            }
        } else {
            // Didn't see 'schm' or 'tenc', so this isn't encrypted.
            if ((aux_info_type == MKBETAG('c','e','n','c') ||
                 aux_info_type == MKBETAG('c','e','n','s') ||
                 aux_info_type == MKBETAG('c','b','c','1') ||
                 aux_info_type == MKBETAG('c','b','c','s')) &&
                aux_info_param == 0) {
                av_log(c->fc, AV_LOG_ERROR, "Saw encrypted saiz without schm/tenc\n");
                return AVERROR_INVALIDDATA;
            } else {
                return 0;
            }
        }
    } else if (!sc->cenc.default_encrypted_sample) {
        // Didn't see 'schm' or 'tenc', so this isn't encrypted.
        return 0;
    }

    encryption_index->auxiliary_info_default_size = avio_r8(pb);
    sample_count = avio_rb32(pb);
    encryption_index->auxiliary_info_sample_count = sample_count;

    if (encryption_index->auxiliary_info_default_size == 0) {
        ret = mov_try_read_block(pb, sample_count, &encryption_index->auxiliary_info_sizes);
        if (ret < 0) {
            av_log(c->fc, AV_LOG_ERROR, "Failed to read the auxiliary info\n");
            return ret;
        }
    }

    if (encryption_index->auxiliary_offsets_count) {
        return mov_parse_auxiliary_info(c, sc, pb, encryption_index);
    }

    return 0;
}