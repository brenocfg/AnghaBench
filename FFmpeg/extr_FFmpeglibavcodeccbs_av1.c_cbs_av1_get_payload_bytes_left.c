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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t cbs_av1_get_payload_bytes_left(GetBitContext *gbc)
{
    GetBitContext tmp = *gbc;
    size_t size = 0;
    for (int i = 0; get_bits_left(&tmp) >= 8; i++) {
        if (get_bits(&tmp, 8))
            size = i;
    }
    return size;
}