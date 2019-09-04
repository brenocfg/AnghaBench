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
struct TYPE_3__ {scalar_t__ buf_size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RL16 (int /*<<< orphan*/ *) ; 
 int AV_RL32 (int /*<<< orphan*/ *) ; 
 int FLIC_CHUNK_MAGIC_1 ; 
 int FLIC_FILE_MAGIC_1 ; 
 int FLIC_FILE_MAGIC_2 ; 
 int FLIC_FILE_MAGIC_3 ; 
 scalar_t__ FLIC_HEADER_SIZE ; 

__attribute__((used)) static int flic_probe(const AVProbeData *p)
{
    int magic_number;

    if(p->buf_size < FLIC_HEADER_SIZE)
        return 0;

    magic_number = AV_RL16(&p->buf[4]);
    if ((magic_number != FLIC_FILE_MAGIC_1) &&
        (magic_number != FLIC_FILE_MAGIC_2) &&
        (magic_number != FLIC_FILE_MAGIC_3))
        return 0;

    if(AV_RL16(&p->buf[0x10]) != FLIC_CHUNK_MAGIC_1){
        if(AV_RL32(&p->buf[0x10]) > 2000)
            return 0;
    }

    if(   AV_RL16(&p->buf[0x08]) > 4096
       || AV_RL16(&p->buf[0x0A]) > 4096)
        return 0;


    return AVPROBE_SCORE_MAX - 1;
}