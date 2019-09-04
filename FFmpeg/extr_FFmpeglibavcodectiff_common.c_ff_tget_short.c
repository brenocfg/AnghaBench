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
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int bytestream2_get_be16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 

unsigned ff_tget_short(GetByteContext *gb, int le)
{
    return le ? bytestream2_get_le16(gb) : bytestream2_get_be16(gb);
}