#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int num_buckets; } ;
typedef  TYPE_1__ HashIndex ;

/* Variables and functions */
 int _le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hashindex_index(HashIndex *index, const unsigned char *key)
{
    return _le32toh(*((uint32_t *)key)) % index->num_buckets;
}