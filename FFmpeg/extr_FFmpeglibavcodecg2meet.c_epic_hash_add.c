#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  pix_id; } ;
typedef  TYPE_1__ ePICPixHashElem ;
struct TYPE_9__ {int* bucket_size; int* bucket_fill; TYPE_1__** bucket; } ;
typedef  TYPE_2__ ePICPixHash ;

/* Variables and functions */
 int INT_MAX ; 
 TYPE_1__* av_realloc (TYPE_1__*,int) ; 
 int djb2_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ePICPixHashElem *epic_hash_add(ePICPixHash *hash, uint32_t key)
{
    ePICPixHashElem *bucket, *ret;
    int idx = djb2_hash(key);

    if (hash->bucket_size[idx] > INT_MAX / sizeof(**hash->bucket))
        return NULL;

    if (!(hash->bucket_fill[idx] < hash->bucket_size[idx])) {
        int new_size = hash->bucket_size[idx] + 16;
        bucket = av_realloc(hash->bucket[idx], new_size * sizeof(*bucket));
        if (!bucket)
            return NULL;
        hash->bucket[idx]      = bucket;
        hash->bucket_size[idx] = new_size;
    }

    ret = &hash->bucket[idx][hash->bucket_fill[idx]++];
    memset(ret, 0, sizeof(*ret));
    ret->pix_id = key;
    return ret;
}