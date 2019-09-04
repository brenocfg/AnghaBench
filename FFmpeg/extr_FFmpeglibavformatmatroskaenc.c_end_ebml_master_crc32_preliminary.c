#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ebml_master ;
struct TYPE_7__ {int seekable; } ;
typedef  int /*<<< orphan*/  MatroskaMuxContext ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 int avio_get_dyn_buf (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_write (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  end_ebml_master (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void end_ebml_master_crc32_preliminary(AVIOContext *pb, AVIOContext **dyn_cp, MatroskaMuxContext *mkv,
    ebml_master master)
{
    if (pb->seekable & AVIO_SEEKABLE_NORMAL) {

        uint8_t *buf;
        int size = avio_get_dyn_buf(*dyn_cp, &buf);

        avio_write(pb, buf, size);
        end_ebml_master(pb, master);
    }
}