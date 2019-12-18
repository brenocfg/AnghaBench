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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  avpriv_dict_set_timestamp (int /*<<< orphan*/ **,char*,int) ; 

__attribute__((used)) static void matroska_metadata_creation_time(AVDictionary **metadata, int64_t date_utc)
{
    /* Convert to seconds and adjust by number of seconds between 2001-01-01 and Epoch */
    avpriv_dict_set_timestamp(metadata, "creation_time", date_utc / 1000 + 978307200000000LL);
}