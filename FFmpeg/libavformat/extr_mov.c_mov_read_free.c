#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  content ;
struct TYPE_6__ {int size; } ;
struct TYPE_5__ {scalar_t__ use_mfra_for; int /*<<< orphan*/  found_mdat; int /*<<< orphan*/  found_moov; } ;
typedef  TYPE_1__ MOVContext ;
typedef  TYPE_2__ MOVAtom ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (int,int) ; 
 scalar_t__ FF_MOV_FLAG_MFRA_AUTO ; 
 scalar_t__ FF_MOV_FLAG_MFRA_PTS ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int mov_read_free(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    int ret;
    uint8_t content[16];

    if (atom.size < 8)
        return 0;

    ret = avio_read(pb, content, FFMIN(sizeof(content), atom.size));
    if (ret < 0)
        return ret;

    if (   !c->found_moov
        && !c->found_mdat
        && !memcmp(content, "Anevia\x1A\x1A", 8)
        && c->use_mfra_for == FF_MOV_FLAG_MFRA_AUTO) {
        c->use_mfra_for = FF_MOV_FLAG_MFRA_PTS;
    }

    return 0;
}