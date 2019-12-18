#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  attr ;
struct TYPE_7__ {char* codec_attr; scalar_t__ attr_status; } ;
typedef  TYPE_2__ VariantStream ;
struct TYPE_8__ {TYPE_1__* codecpar; } ;
struct TYPE_6__ {scalar_t__ codec_type; scalar_t__ codec_id; int* extradata; } ;
typedef  TYPE_3__ AVStream ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 scalar_t__ AV_CODEC_ID_AAC ; 
 scalar_t__ AV_CODEC_ID_AC3 ; 
 scalar_t__ AV_CODEC_ID_EAC3 ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_MP2 ; 
 scalar_t__ AV_CODEC_ID_MP3 ; 
 scalar_t__ CODEC_ATTRIBUTE_WILL_NOT_BE_WRITTEN ; 
 int /*<<< orphan*/  av_stristr (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static void write_codec_attr(AVStream *st, VariantStream *vs)
{
    int codec_strlen = strlen(vs->codec_attr);
    char attr[32];

    if (st->codecpar->codec_type == AVMEDIA_TYPE_SUBTITLE)
        return;
    if (vs->attr_status == CODEC_ATTRIBUTE_WILL_NOT_BE_WRITTEN)
        return;

    if (st->codecpar->codec_id == AV_CODEC_ID_H264) {
        uint8_t *data = st->codecpar->extradata;
        if (data && (data[0] | data[1] | data[2]) == 0 && data[3] == 1 && (data[4] & 0x1F) == 7) {
            snprintf(attr, sizeof(attr),
                     "avc1.%02x%02x%02x", data[5], data[6], data[7]);
        } else {
            goto fail;
        }
    } else if (st->codecpar->codec_id == AV_CODEC_ID_MP2) {
        snprintf(attr, sizeof(attr), "mp4a.40.33");
    } else if (st->codecpar->codec_id == AV_CODEC_ID_MP3) {
        snprintf(attr, sizeof(attr), "mp4a.40.34");
    } else if (st->codecpar->codec_id == AV_CODEC_ID_AAC) {
        /* TODO : For HE-AAC, HE-AACv2, the last digit needs to be set to 5 and 29 respectively */
        snprintf(attr, sizeof(attr), "mp4a.40.2");
    } else if (st->codecpar->codec_id == AV_CODEC_ID_AC3) {
        snprintf(attr, sizeof(attr), "ac-3");
    } else if (st->codecpar->codec_id == AV_CODEC_ID_EAC3) {
        snprintf(attr, sizeof(attr), "ec-3");
    } else {
        goto fail;
    }
    // Don't write the same attribute multiple times
    if (!av_stristr(vs->codec_attr, attr)) {
        snprintf(vs->codec_attr + codec_strlen,
                 sizeof(vs->codec_attr) - codec_strlen,
                 "%s%s", codec_strlen ? "," : "", attr);
    }
    return;

fail:
    vs->codec_attr[0] = '\0';
    vs->attr_status = CODEC_ATTRIBUTE_WILL_NOT_BE_WRITTEN;
    return;
}