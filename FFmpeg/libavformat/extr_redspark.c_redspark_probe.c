#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB32 (scalar_t__) ; 
 scalar_t__ AV_RB64 (char*) ; 
 int /*<<< orphan*/  AV_WB32 (char*,int) ; 
 int rol (int,int) ; 

__attribute__((used)) static int redspark_probe(const AVProbeData *p)
{
    uint32_t key, data;
    uint8_t header[8];

    /* Decrypt first 8 bytes of the header */
    data = AV_RB32(p->buf);
    key  = data ^ 0x52656453;
    data ^= key;
    AV_WB32(header, data);
    key = rol(key, 11);

    key += rol(key, 3);
    data = AV_RB32(p->buf + 4) ^ key;
    AV_WB32(header + 4, data);

    if (AV_RB64(header) == AV_RB64("RedSpark"))
        return AVPROBE_SCORE_MAX;

    return 0;
}