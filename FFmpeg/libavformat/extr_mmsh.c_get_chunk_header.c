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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  mms_hd; } ;
struct TYPE_4__ {int /*<<< orphan*/  chunk_seq; TYPE_2__ mms; } ;
typedef  TYPE_1__ MMSHContext ;
typedef  TYPE_2__ MMSContext ;
typedef  int ChunkType ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RL16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_RL32 (int /*<<< orphan*/ *) ; 
 int CHUNK_HEADER_LENGTH ; 
#define  CHUNK_TYPE_ASF_HEADER 131 
#define  CHUNK_TYPE_DATA 130 
#define  CHUNK_TYPE_END 129 
#define  CHUNK_TYPE_STREAM_CHANGE 128 
 int /*<<< orphan*/  EIO ; 
 int EXT_HEADER_LENGTH ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int ffurl_read_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ChunkType get_chunk_header(MMSHContext *mmsh, int *len)
{
    MMSContext *mms = &mmsh->mms;
    uint8_t chunk_header[CHUNK_HEADER_LENGTH];
    uint8_t ext_header[EXT_HEADER_LENGTH];
    ChunkType chunk_type;
    int chunk_len, res, ext_header_len;

    res = ffurl_read_complete(mms->mms_hd, chunk_header, CHUNK_HEADER_LENGTH);
    if (res != CHUNK_HEADER_LENGTH) {
        av_log(NULL, AV_LOG_ERROR, "Read data packet header failed!\n");
        return AVERROR(EIO);
    }
    chunk_type = AV_RL16(chunk_header);
    chunk_len  = AV_RL16(chunk_header + 2);

    switch (chunk_type) {
    case CHUNK_TYPE_END:
    case CHUNK_TYPE_STREAM_CHANGE:
        ext_header_len = 4;
        break;
    case CHUNK_TYPE_ASF_HEADER:
    case CHUNK_TYPE_DATA:
        ext_header_len = 8;
        break;
    default:
        av_log(NULL, AV_LOG_ERROR, "Strange chunk type %d\n", chunk_type);
        return AVERROR_INVALIDDATA;
    }

    res = ffurl_read_complete(mms->mms_hd, ext_header, ext_header_len);
    if (res != ext_header_len) {
        av_log(NULL, AV_LOG_ERROR, "Read ext header failed!\n");
        return AVERROR(EIO);
    }
    *len = chunk_len - ext_header_len;
    if (chunk_type == CHUNK_TYPE_END || chunk_type == CHUNK_TYPE_DATA)
        mmsh->chunk_seq = AV_RL32(ext_header);
    return chunk_type;
}