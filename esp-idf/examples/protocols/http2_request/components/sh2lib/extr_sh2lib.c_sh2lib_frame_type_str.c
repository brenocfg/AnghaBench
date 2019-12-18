#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  NGHTTP2_DATA 134 
#define  NGHTTP2_GOAWAY 133 
#define  NGHTTP2_HEADERS 132 
#define  NGHTTP2_PING 131 
#define  NGHTTP2_PUSH_PROMISE 130 
#define  NGHTTP2_RST_STREAM 129 
#define  NGHTTP2_SETTINGS 128 

const char *sh2lib_frame_type_str(int type)
{
    switch (type) {
    case NGHTTP2_HEADERS:
        return "HEADERS";
        break;
    case NGHTTP2_RST_STREAM:
        return "RST_STREAM";
        break;
    case NGHTTP2_GOAWAY:
        return "GOAWAY";
        break;
    case NGHTTP2_DATA:
        return "DATA";
        break;
    case NGHTTP2_SETTINGS:
        return "SETTINGS";
        break;
    case NGHTTP2_PUSH_PROMISE:
        return "PUSH_PROMISE";
        break;
    case NGHTTP2_PING:
        return "PING";
        break;
    default:
        return "other";
        break;
    }
}