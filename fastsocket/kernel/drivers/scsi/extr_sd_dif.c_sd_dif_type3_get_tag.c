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
typedef  int u8 ;
struct sd_dif_tuple {int app_tag; int ref_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static void sd_dif_type3_get_tag(void *prot, void *tag_buf, unsigned int sectors)
{
	struct sd_dif_tuple *sdt = prot;
	u8 *tag = tag_buf;
	unsigned int i, j;

	for (i = 0, j = 0 ; i < sectors ; i++, j += 2, sdt++) {
		tag[j] = (sdt->app_tag & 0xff00) >> 8;
		tag[j+1] = sdt->app_tag & 0xff;
		tag[j+2] = (sdt->ref_tag & 0xff000000) >> 24;
		tag[j+3] = (sdt->ref_tag & 0xff0000) >> 16;
		tag[j+4] = (sdt->ref_tag & 0xff00) >> 8;
		tag[j+5] = sdt->ref_tag & 0xff;
		BUG_ON(sdt->app_tag == 0xffff || sdt->ref_tag == 0xffffffff);
	}
}