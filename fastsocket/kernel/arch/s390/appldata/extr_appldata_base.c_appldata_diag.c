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
typedef  int /*<<< orphan*/  u16 ;
struct appldata_product_id {int prod_fn; int version_nr; int release_nr; char record_nr; char mod_lvl; int /*<<< orphan*/  prod_nr; } ;

/* Variables and functions */
 int appldata_asm (struct appldata_product_id*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int appldata_diag(char record_nr, u16 function, unsigned long buffer,
			u16 length, char *mod_lvl)
{
	struct appldata_product_id id = {
		.prod_nr    = {0xD3, 0xC9, 0xD5, 0xE4,
			       0xE7, 0xD2, 0xD9},	/* "LINUXKR" */
		.prod_fn    = 0xD5D3,			/* "NL" */
		.version_nr = 0xF2F6,			/* "26" */
		.release_nr = 0xF0F1,			/* "01" */
	};

	id.record_nr = record_nr;
	id.mod_lvl = (mod_lvl[0]) << 8 | mod_lvl[1];
	return appldata_asm(&id, function, (void *) buffer, length);
}