#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_26__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_25__ {int /*<<< orphan*/  id; } ;
struct TYPE_19__ {int stsd_id; } ;
struct TYPE_18__ {int /*<<< orphan*/  current; } ;
struct TYPE_24__ {scalar_t__ decryption_key; int /*<<< orphan*/  fc; TYPE_1__ fragment; TYPE_10__ frag_index; } ;
struct TYPE_23__ {int nb_encrypted_samples; int /*<<< orphan*/ ** encrypted_samples; scalar_t__ auxiliary_offsets_count; scalar_t__ auxiliary_info_sample_count; } ;
struct TYPE_22__ {int index_entry; TYPE_5__* encryption_index; } ;
struct TYPE_20__ {int /*<<< orphan*/ * default_encrypted_sample; TYPE_5__* encryption_index; } ;
struct TYPE_21__ {TYPE_2__ cenc; } ;
typedef  TYPE_3__ MOVStreamContext ;
typedef  TYPE_4__ MOVFragmentStreamInfo ;
typedef  TYPE_5__ MOVEncryptionIndex ;
typedef  TYPE_6__ MOVContext ;
typedef  TYPE_7__ AVStream ;
typedef  TYPE_8__ AVPacket ;
typedef  int /*<<< orphan*/  AVEncryptionInfo ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_ENCRYPTION_INFO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_encryption_info_add_side_data (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int av_packet_add_side_data (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int cenc_decrypt (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* get_frag_stream_info (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cenc_filter(MOVContext *mov, AVStream* st, MOVStreamContext *sc, AVPacket *pkt, int current_index)
{
    MOVFragmentStreamInfo *frag_stream_info;
    MOVEncryptionIndex *encryption_index;
    AVEncryptionInfo *encrypted_sample;
    int encrypted_index, ret;

    frag_stream_info = get_frag_stream_info(&mov->frag_index, mov->frag_index.current, st->id);
    encrypted_index = current_index;
    encryption_index = NULL;
    if (frag_stream_info) {
        // Note this only supports encryption info in the first sample descriptor.
        if (mov->fragment.stsd_id == 1) {
            if (frag_stream_info->encryption_index) {
                encrypted_index = current_index - frag_stream_info->index_entry;
                encryption_index = frag_stream_info->encryption_index;
            } else {
                encryption_index = sc->cenc.encryption_index;
            }
        }
    } else {
        encryption_index = sc->cenc.encryption_index;
    }

    if (encryption_index) {
        if (encryption_index->auxiliary_info_sample_count &&
            !encryption_index->nb_encrypted_samples) {
            av_log(mov->fc, AV_LOG_ERROR, "saiz atom found without saio\n");
            return AVERROR_INVALIDDATA;
        }
        if (encryption_index->auxiliary_offsets_count &&
            !encryption_index->nb_encrypted_samples) {
            av_log(mov->fc, AV_LOG_ERROR, "saio atom found without saiz\n");
            return AVERROR_INVALIDDATA;
        }

        if (!encryption_index->nb_encrypted_samples) {
            // Full-sample encryption with default settings.
            encrypted_sample = sc->cenc.default_encrypted_sample;
        } else if (encrypted_index >= 0 && encrypted_index < encryption_index->nb_encrypted_samples) {
            // Per-sample setting override.
            encrypted_sample = encryption_index->encrypted_samples[encrypted_index];
        } else {
            av_log(mov->fc, AV_LOG_ERROR, "Incorrect number of samples in encryption info\n");
            return AVERROR_INVALIDDATA;
        }

        if (mov->decryption_key) {
            return cenc_decrypt(mov, sc, encrypted_sample, pkt->data, pkt->size);
        } else {
            size_t size;
            uint8_t *side_data = av_encryption_info_add_side_data(encrypted_sample, &size);
            if (!side_data)
                return AVERROR(ENOMEM);
            ret = av_packet_add_side_data(pkt, AV_PKT_DATA_ENCRYPTION_INFO, side_data, size);
            if (ret < 0)
                av_free(side_data);
            return ret;
        }
    }

    return 0;
}