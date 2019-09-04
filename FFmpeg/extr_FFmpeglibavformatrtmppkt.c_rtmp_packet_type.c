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
#define  RTMP_PT_AUDIO 141 
#define  RTMP_PT_BYTES_READ 140 
#define  RTMP_PT_CHUNK_SIZE 139 
#define  RTMP_PT_FLEX_MESSAGE 138 
#define  RTMP_PT_FLEX_OBJECT 137 
#define  RTMP_PT_FLEX_STREAM 136 
#define  RTMP_PT_INVOKE 135 
#define  RTMP_PT_METADATA 134 
#define  RTMP_PT_NOTIFY 133 
#define  RTMP_PT_SET_PEER_BW 132 
#define  RTMP_PT_SHARED_OBJ 131 
#define  RTMP_PT_USER_CONTROL 130 
#define  RTMP_PT_VIDEO 129 
#define  RTMP_PT_WINDOW_ACK_SIZE 128 

__attribute__((used)) static const char* rtmp_packet_type(int type)
{
    switch (type) {
    case RTMP_PT_CHUNK_SIZE:     return "chunk size";
    case RTMP_PT_BYTES_READ:     return "bytes read";
    case RTMP_PT_USER_CONTROL:   return "user control";
    case RTMP_PT_WINDOW_ACK_SIZE: return "window acknowledgement size";
    case RTMP_PT_SET_PEER_BW:    return "set peer bandwidth";
    case RTMP_PT_AUDIO:          return "audio packet";
    case RTMP_PT_VIDEO:          return "video packet";
    case RTMP_PT_FLEX_STREAM:    return "Flex shared stream";
    case RTMP_PT_FLEX_OBJECT:    return "Flex shared object";
    case RTMP_PT_FLEX_MESSAGE:   return "Flex shared message";
    case RTMP_PT_NOTIFY:         return "notification";
    case RTMP_PT_SHARED_OBJ:     return "shared object";
    case RTMP_PT_INVOKE:         return "invoke";
    case RTMP_PT_METADATA:       return "metadata";
    default:                     return "unknown";
    }
}