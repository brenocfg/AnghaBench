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
typedef  int* UID ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxf_header_partition_pack_key ; 

__attribute__((used)) static int mxf_is_partition_pack_key(UID key)
{
    //NOTE: this is a little lax since it doesn't constraint key[14]
    return !memcmp(key, mxf_header_partition_pack_key, 13) &&
            key[13] >= 2 && key[13] <= 4;
}