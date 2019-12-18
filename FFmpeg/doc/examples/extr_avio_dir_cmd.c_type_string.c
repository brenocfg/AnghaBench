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
#define  AVIO_ENTRY_BLOCK_DEVICE 138 
#define  AVIO_ENTRY_CHARACTER_DEVICE 137 
#define  AVIO_ENTRY_DIRECTORY 136 
#define  AVIO_ENTRY_FILE 135 
#define  AVIO_ENTRY_NAMED_PIPE 134 
#define  AVIO_ENTRY_SERVER 133 
#define  AVIO_ENTRY_SHARE 132 
#define  AVIO_ENTRY_SOCKET 131 
#define  AVIO_ENTRY_SYMBOLIC_LINK 130 
#define  AVIO_ENTRY_UNKNOWN 129 
#define  AVIO_ENTRY_WORKGROUP 128 

__attribute__((used)) static const char *type_string(int type)
{
    switch (type) {
    case AVIO_ENTRY_DIRECTORY:
        return "<DIR>";
    case AVIO_ENTRY_FILE:
        return "<FILE>";
    case AVIO_ENTRY_BLOCK_DEVICE:
        return "<BLOCK DEVICE>";
    case AVIO_ENTRY_CHARACTER_DEVICE:
        return "<CHARACTER DEVICE>";
    case AVIO_ENTRY_NAMED_PIPE:
        return "<PIPE>";
    case AVIO_ENTRY_SYMBOLIC_LINK:
        return "<LINK>";
    case AVIO_ENTRY_SOCKET:
        return "<SOCKET>";
    case AVIO_ENTRY_SERVER:
        return "<SERVER>";
    case AVIO_ENTRY_SHARE:
        return "<SHARE>";
    case AVIO_ENTRY_WORKGROUP:
        return "<WORKGROUP>";
    case AVIO_ENTRY_UNKNOWN:
    default:
        break;
    }
    return "<UNKNOWN>";
}