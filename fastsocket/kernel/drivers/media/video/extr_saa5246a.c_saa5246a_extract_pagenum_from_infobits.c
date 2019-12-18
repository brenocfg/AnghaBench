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
 unsigned char ROW25_COLUMN0_PAGE_UNITS ; 
 unsigned char ROW25_COLUMN1_PAGE_TENS ; 
 unsigned char ROW25_COLUMN8_PAGE_HUNDREDS ; 

__attribute__((used)) static inline int saa5246a_extract_pagenum_from_infobits(
    unsigned char infobits[10])
{
	int page_hundreds, page_tens, page_units;

	page_units    = infobits[0] & ROW25_COLUMN0_PAGE_UNITS;
	page_tens     = infobits[1] & ROW25_COLUMN1_PAGE_TENS;
	page_hundreds = infobits[8] & ROW25_COLUMN8_PAGE_HUNDREDS;

	/* page 0x.. means page 8.. */
	if (page_hundreds == 0)
		page_hundreds = 8;

	return((page_hundreds << 8) | (page_tens << 4) | page_units);
}