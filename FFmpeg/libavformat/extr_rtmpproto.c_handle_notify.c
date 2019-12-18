#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  statusmsg ;
typedef  int /*<<< orphan*/  commandbuffer ;
struct TYPE_16__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_19__ {int buffer; int /*<<< orphan*/  buffer_end; } ;
struct TYPE_18__ {int received_metadata; int has_video; int has_audio; } ;
struct TYPE_17__ {int data; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ RTMPPacket ;
typedef  TYPE_3__ RTMPContext ;
typedef  TYPE_4__ GetByteContext ;

/* Variables and functions */
 scalar_t__ AMF_DATA_TYPE_MIXEDARRAY ; 
 scalar_t__ AMF_END_OF_OBJECT ; 
 int AVERROR_INVALIDDATA ; 
 int append_flv_data (TYPE_3__*,TYPE_2__*,int) ; 
 scalar_t__ bytestream2_get_be24 (TYPE_4__*) ; 
 scalar_t__ bytestream2_get_byte (TYPE_4__*) ; 
 int bytestream2_get_bytes_left (TYPE_4__*) ; 
 int /*<<< orphan*/  bytestream2_init (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_skip (TYPE_4__*,int) ; 
 scalar_t__ ff_amf_get_string (TYPE_4__*,char*,int,int*) ; 
 int ff_amf_read_string (TYPE_4__*,char*,int,int*) ; 
 int ff_amf_tag_size (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int handle_notify(URLContext *s, RTMPPacket *pkt)
{
    RTMPContext *rt  = s->priv_data;
    uint8_t commandbuffer[64];
    char statusmsg[128];
    int stringlen, ret, skip = 0;
    GetByteContext gbc;

    bytestream2_init(&gbc, pkt->data, pkt->size);
    if (ff_amf_read_string(&gbc, commandbuffer, sizeof(commandbuffer),
                           &stringlen))
        return AVERROR_INVALIDDATA;

    if (!strcmp(commandbuffer, "onMetaData")) {
        // metadata properties should be stored in a mixed array
        if (bytestream2_get_byte(&gbc) == AMF_DATA_TYPE_MIXEDARRAY) {
            // We have found a metaData Array so flv can determine the streams
            // from this.
            rt->received_metadata = 1;
            // skip 32-bit max array index
            bytestream2_skip(&gbc, 4);
            while (bytestream2_get_bytes_left(&gbc) > 3) {
                if (ff_amf_get_string(&gbc, statusmsg, sizeof(statusmsg),
                                      &stringlen))
                    return AVERROR_INVALIDDATA;
                // We do not care about the content of the property (yet).
                stringlen = ff_amf_tag_size(gbc.buffer, gbc.buffer_end);
                if (stringlen < 0)
                    return AVERROR_INVALIDDATA;
                bytestream2_skip(&gbc, stringlen);

                // The presence of the following properties indicates that the
                // respective streams are present.
                if (!strcmp(statusmsg, "videocodecid")) {
                    rt->has_video = 1;
                }
                if (!strcmp(statusmsg, "audiocodecid")) {
                    rt->has_audio = 1;
                }
            }
            if (bytestream2_get_be24(&gbc) != AMF_END_OF_OBJECT)
                return AVERROR_INVALIDDATA;
        }
    }

    // Skip the @setDataFrame string and validate it is a notification
    if (!strcmp(commandbuffer, "@setDataFrame")) {
        skip = gbc.buffer - pkt->data;
        ret = ff_amf_read_string(&gbc, statusmsg,
                                 sizeof(statusmsg), &stringlen);
        if (ret < 0)
            return AVERROR_INVALIDDATA;
    }

    return append_flv_data(rt, pkt, skip);
}