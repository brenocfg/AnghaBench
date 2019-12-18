#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ pix_id; } ;
typedef  TYPE_1__ ePICPixHashElem ;
struct TYPE_6__ {int* bucket_fill; TYPE_1__** bucket; } ;
typedef  TYPE_2__ ePICPixHash ;

/* Variables and functions */
 int djb2_hash (scalar_t__) ; 

__attribute__((used)) static ePICPixHashElem *epic_hash_find(const ePICPixHash *hash, uint32_t key)
{
    int i, idx = djb2_hash(key);
    ePICPixHashElem *bucket = hash->bucket[idx];

    for (i = 0; i < hash->bucket_fill[idx]; i++)
        if (bucket[i].pix_id == key)
            return &bucket[i];

    return NULL;
}