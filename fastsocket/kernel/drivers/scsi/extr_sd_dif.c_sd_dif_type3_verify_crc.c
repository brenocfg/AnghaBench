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
struct blk_integrity_exchg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sd_dif_crc_fn ; 
 int sd_dif_type3_verify (struct blk_integrity_exchg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_dif_type3_verify_crc(struct blk_integrity_exchg *bix)
{
	return sd_dif_type3_verify(bix, sd_dif_crc_fn);
}