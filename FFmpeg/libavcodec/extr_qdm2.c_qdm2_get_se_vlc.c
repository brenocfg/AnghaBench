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
typedef  int /*<<< orphan*/  VLC ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int qdm2_get_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qdm2_get_se_vlc(const VLC *vlc, GetBitContext *gb, int depth)
{
    int value = qdm2_get_vlc(gb, vlc, 0, depth);

    return (value & 1) ? ((value + 1) >> 1) : -(value >> 1);
}