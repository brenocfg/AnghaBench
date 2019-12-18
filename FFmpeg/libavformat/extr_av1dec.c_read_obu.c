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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int parse_obu_header (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int*,int*,int*,int*) ; 

__attribute__((used)) static int read_obu(const uint8_t *buf, int size, int64_t *obu_size, int *type)
{
    int start_pos, temporal_id, spatial_id;
    int len;

    len = parse_obu_header(buf, size, obu_size, &start_pos,
                           type, &temporal_id, &spatial_id);
    if (len < 0)
        return len;

    return 0;
}