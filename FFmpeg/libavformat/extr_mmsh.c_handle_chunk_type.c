#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  header_parsed; } ;
struct TYPE_7__ {int /*<<< orphan*/  chunk_seq; TYPE_2__ mms; } ;
typedef  TYPE_1__ MMSHContext ;
typedef  TYPE_2__ MMSContext ;
typedef  int ChunkType ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  CHUNK_TYPE_DATA 130 
#define  CHUNK_TYPE_END 129 
#define  CHUNK_TYPE_STREAM_CHANGE 128 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int get_chunk_header (TYPE_1__*,int*) ; 
 int get_http_header_data (TYPE_1__*) ; 
 int read_data_packet (TYPE_1__*,int) ; 

__attribute__((used)) static int handle_chunk_type(MMSHContext *mmsh)
{
    MMSContext *mms = &mmsh->mms;
    int res, len = 0;
    ChunkType chunk_type;
    chunk_type = get_chunk_header(mmsh, &len);

    switch (chunk_type) {
    case CHUNK_TYPE_END:
        mmsh->chunk_seq = 0;
        av_log(NULL, AV_LOG_ERROR, "Stream ended!\n");
        return AVERROR(EIO);
    case CHUNK_TYPE_STREAM_CHANGE:
        mms->header_parsed = 0;
        if (res = get_http_header_data(mmsh)) {
            av_log(NULL, AV_LOG_ERROR,"Stream changed! Failed to get new header!\n");
            return res;
        }
        break;
    case CHUNK_TYPE_DATA:
        return read_data_packet(mmsh, len);
    default:
        av_log(NULL, AV_LOG_ERROR, "Recv other type packet %d\n", chunk_type);
        return AVERROR_INVALIDDATA;
    }
    return 0;
}