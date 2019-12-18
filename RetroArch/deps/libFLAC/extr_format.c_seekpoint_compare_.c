#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ sample_number; } ;
typedef  TYPE_1__ FLAC__StreamMetadata_SeekPoint ;

/* Variables and functions */

__attribute__((used)) static int seekpoint_compare_(const FLAC__StreamMetadata_SeekPoint *l, const FLAC__StreamMetadata_SeekPoint *r)
{
	/* we don't just 'return l->sample_number - r->sample_number' since the result (FLAC__int64) might overflow an 'int' */
	if(l->sample_number == r->sample_number)
		return 0;
	else if(l->sample_number < r->sample_number)
		return -1;
	else
		return 1;
}