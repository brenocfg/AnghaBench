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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
#define  ASF_BOOL 131 
#define  ASF_DWORD 130 
#define  ASF_QWORD 129 
#define  ASF_WORD 128 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asf_read_generic_value(AVIOContext *pb, int type, uint64_t *value)
{

    switch (type) {
    case ASF_BOOL:
        *value = avio_rl16(pb);
        break;
    case ASF_DWORD:
        *value = avio_rl32(pb);
        break;
    case ASF_QWORD:
        *value = avio_rl64(pb);
        break;
    case ASF_WORD:
        *value = avio_rl16(pb);
        break;
    default:
        return AVERROR_INVALIDDATA;
    }

    return 0;
}