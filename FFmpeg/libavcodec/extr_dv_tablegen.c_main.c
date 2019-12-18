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
 int /*<<< orphan*/  DV_VLC_MAP_LEV_SIZE ; 
 int /*<<< orphan*/  DV_VLC_MAP_RUN_SIZE ; 
 int /*<<< orphan*/  dv_vlc_map ; 
 int /*<<< orphan*/  dv_vlc_map_tableinit () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  write_dv_vlc_pair_2d_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fileheader () ; 

int main(void)
{
    dv_vlc_map_tableinit();

    write_fileheader();

    printf("static const struct dv_vlc_pair dv_vlc_map[DV_VLC_MAP_RUN_SIZE][DV_VLC_MAP_LEV_SIZE] = {\n");
    write_dv_vlc_pair_2d_array(dv_vlc_map, DV_VLC_MAP_RUN_SIZE, DV_VLC_MAP_LEV_SIZE);
    printf("};\n");

    return 0;
}